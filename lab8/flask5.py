#!/usr/bin/python3

from flask import Flask
from flask import make_response

app= Flask(__name__)

@app.route('/<greeting>/<name>')
def greet(greeting,name):
    resp = make_response(f'{greeting},{name}!',404)
    resp.headers['MY_HEADER'] = 1234
    return resp

#단독으로 실행되면, name이 main 으로 실행된다. import 시 내부 설정이 실행되지 않음. 
if __name__ == '__main__':
    app.run(host = '0.0.0.0',port=19142)
