from flask import Flask

app = Flask(__name__)


@app.route("/")  #decorator인데, '/' url 에 대한 이벤트 핸들링을 진행한다. 
def hello_world():
    return 'Hello, World!'

@app.route('/bad',methods=['GET','POST'])
def bad_world():
    return 'Bad World!'

@app.route('/good')
def good_world():
    return 'Good World!'

#단독으로 실행되면, name이 main 으로 실행된다. import 시 내부 설정이 실행되지 않음. 
if __name__ == '__main__':
    app.run(host = '0.0.0.0',port=19142)