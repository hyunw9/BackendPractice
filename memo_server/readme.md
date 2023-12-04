# readme.md
# 실행 환경

## Stack 
1. Python
2. Uwsgi
3. Nginx
4. Ec2
5. Elastic loadbalencer
6. Docker
7. Redis

### AWS 실행 환경 
2대의 독립된 EC2 인스턴스에 memo.py 코드가 올라가 실행되고 있습니다.
데이터베이스는 인메모리 DB인 redis 를 사용하였습니다.
데이터베이스 서버는 EC2 인스턴스 위에 redis docker image 를 띄워서 외부에서도 6379 번으로 접근 할 수 있도록 구성하였습니다. 

실행 흐름과 원리 
1. http://내 lb dns/memo 로 접속 (http)
2. 두 대의 서버 앞에 존재하는 loadbalencer 가 80 번 포트로 들어오는 연결을 8000 번 포트로 변환
   (nginx 설정 기본 값)
3. Nginx 는 8000번 포트로 들어오는 연결을 url에 따라 행동을 특정합니다. 
   본 환경에서는 /memo 로 들어오는 요청을 127.0.0.1:10001 uwsgi 에 전달합니다. 
4. Uwsgi 는 127.0.0.1:10001/memo 로 들어온 요청을 분석합니다.
   127.0.0.1 은 로컬, 10001번 포트에 열린 memo.py(app)을 실행하고, prefix 를 제거하도록 설정하였습니다. 결론적으로 http://60192159-lb-1689628747.ap-northeast-2.elb.amazonaws.com/memo/ 로 보내는 요청은  memo.py 에 app.route(‘/‘) 로 전달되게 됩니다. 

![](readme/image.png)

## 코드 설명
```
r = redis.Redis(host='3.38.253.73',port=6379 ,password="1234", db = 0)
//DB를 EC2 인스턴스에 docker 로 가상화 하여 올렸으므로, 커넥션 풀 설정을 변경했습니다. 
```

```
naver_redirect_uri = 'http://60192159-lb-1689628747.ap-northeast-2.elb.amazonaws.com:80/auth'
// redirect url 을 변경했습니다. 
```



```
# 1. redirect uri 를 호출한 request 로부터 authorization code 와 state 정보를 얻어낸다.
    url = request.url
    parsedUrl = urllib.parse.urlparse(url)
    query_params = urllib.parse.parse_qs(parsedUrl.query)
    
    code = query_params.get('code')[0]
    state = query_params.get('state')[0]

    # 2. authorization code 로부터 access token 을 얻어내는 네이버 API 를 호출한다.

    params = {
        'grant_type': 'authorization_code',
        'client_id' : naver_client_id,
        'client_secret' : naver_client_secret,
        'code' : code,
        'state': state,
    }
    urlencoded = urllib.parse.urlencode(params)  
    url = f'https://nid.naver.com/oauth2.0/token?{urlencoded}'

    response = requests.get(url) 
    # 3. 얻어낸  access token을 이용해서 프로필 정보를 반환하는 API 를 호출하고,
    #    유저의 고유 식별 번호를 얻어낸다.
    data = response.json()
    access_token = data.get('access_token')
    refresh_token = data.get('refresh_token')
    token_type = data.get('token_type')
    expires_in = data.get('expires_in')

    header = "Bearer " + access_token
    
    url = f'https://openapi.naver.com/v1/nid/me'
    urlrequest = urllib.request.Request(url)
    urlrequest.add_header("Authorization",header)
    response = urllib.request.urlopen(urlrequest)
    rescode = response.getcode()
    if rescode == 200:
        response_body = response.read()
        print(response_body.decode('utf-8'))
    else:
        print("Error Code:" + rescode)

    decoded = response_body.decode('utf-8')
    data = json.loads(decoded)
    
    # 4. 얻어낸 user id 와 name 을 DB 에 저장한다.
    user_id = data.get('response').get('id')
    user_name = data.get('response').get('name')
    r.set(user_id,user_name)
	
	//얻어낸 데이터를 userid:username 으로 저장합니다. 

    # 5. 첫 페이지로 redirect 하는데 로그인 쿠키를 설정하고 보내준다.
    response = redirect('/memo')
    response.set_cookie('userId', user_id)
    return response

```

```
# TODO: DB 에서 해당 userId 의 메모들을 읽어오도록 아래를 수정한다.
    key = "memo:"+userId
    result = r.lrange(key,0,-1)
    print(result)
    # memos라는 키 값으로 메모 목록 보내주기
    memos = r.lrange(key, 0, -1)
    memos = [{'text': memo.decode('utf-8')} for memo in memos]
    return jsonify({'memos': memos})

//memo:userId 형식으로 저장된 memo 배열을 읽어와서, json 으로 변환 후 반환합니다.
```

```
# TODO: 클라이언트로부터 받은 JSON 에서 메모 내용을 추출한 후 DB에 userId 의 메모로 추가한다.
    decoded =request.get_json()
    text = decoded['text']
    key = "memo:"+userId 
    r.lpush(key,text)
    
    return '', HTTPStatus.OK
//데이터를 저장 시 , memo:userId : memo[text] 배열 형식으로 저장합니다. 

```

```
# TODO: 아래 부분을 채워 넣으시오.
    #       userId 로부터 DB 에서 사용자 이름을 얻어오는 코드를 여기에 작성해야 함
        
    if userId is not None:
        name = r.get(userId)
        if name is not None:
            name = name.decode('utf-8')
//db에 저장된 userId 가 없다면 로그인 하지 않은 것이므로, 로그인 요청을 받습니다. 
```


```
//uwsgi 가 파일을 인식하는 포트는 10001 번이므로, 수정했습니다. 
if __name__ == '__main__':
    app.run('0.0.0.0', port=10001, debug=True) 

```
