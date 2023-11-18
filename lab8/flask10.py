#!/usr/bin/python3

from flask import Flask
from flask import request
from flask import make_response

app = Flask(__name__)

@app.route('/<num1>/<op>/<num2>')
def calculate(num1,op,num2):
    a,b = int(num1),int(num2)
    ans = 0
    if op == '+' : 
        ans = a + b
    elif op == "-" :
        ans = a - b
    elif op =="*":
        ans = a * b
    resp = make_response(f'{ans}',200)
    return resp
    
@app.route('/' ,methods= ['POST'])
def index():
    a = request.get_json().get('arg1')
    b = request.get_json().get('arg2')
    op = request.get_json().get('op')
    res = 0
    if op == '+':
        res = a+b 
    elif op == '-':
        res = a-b
    elif op == '*':
        res = a*b

    return{
        'arg1' :a,
        'op': op,
        'arg2':b,
        'result' : res
    }
 
    

if __name__ == '__main__':
    app.run(host = '0.0.0.0',port=19142)
