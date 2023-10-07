import json
import socket
import sys

def main(argv):
    obj1 = {
        'name' : 'DK Moon',
        'id' : 12345678,
        'work': {
            'name' : 'Myongji University',
            'address': '116 Myongji-ro'
        },
        'scores':[100,90.5,80.0]
    }
    
    s = json.dumps(obj1,indent = 2)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
    sock.sendto(bytes(s,encoding = 'utf-8'), ('127.0.0.1',10001))
    (data,sender) = sock.recvfrom(65536)
    obj2 = json.loads(data)
    
    print(obj2['name'])
    print(obj2['id'])
    print(obj2['work']['name'])
    print(obj2['scores'][1])
    
if __name__ == '__main__':
    main(sys.argv)
    