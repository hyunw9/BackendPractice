#!/usr/bin/python3

from flask import Flask
from flask import request

app= Flask(__name__)

@app.route('/',methods = ['GET','POST'])
def index():
    method = request.method
    name = request.args.get('name', default ='이름이 없는자')
    client = request.headers['User-Agent']
    return f'{name}, 그대는 {method}로 호출하였구나. 그대는 {client}검을 쓰는군.'    

#단독으로 실행되면, name이 main 으로 실행된다. import 시 내부 설정이 실행되지 않음. 
if __name__ == '__main__':
    app.run(host = '0.0.0.0',port=19142)
