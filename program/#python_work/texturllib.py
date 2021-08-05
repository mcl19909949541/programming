import urllib.request

baseurl = "http://www.baidu.com/"
#获取get请求
# response = urllib.request.urlopen(baseurl)
# print(response.read().decode("utf-8"))

response = urllib.request.urlopen(baseurl)
print(response.getheaders())