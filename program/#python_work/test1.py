import requests
import time

from bs4 import BeautifulSoup
i=1

while True:
    file=open('b.txt', 'r',encoding='utf-8',errors='ignore')
    while True:
        url=file.readline().rstrip()

        header={"user-agent":"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36"}

        try:
            data=requests.get(url=url,headers=header)
        except ValueError:
            break
        else:
            print(data.status_code,end='')
            if(data.status_code == 200):
                print(f"访问{url}成功")
            else:
                print(f"访问{url}失败")
            time.sleep(3)
    file.close()
    print(f"第{i}轮")
    time.sleep(30)
    i+=1

