# 导入urllib下的request模块
import urllib.request
# 导入正则匹配包
import re

# -*- encoding:utf-8 -*-

# 步骤
# 1.确定要爬取数据的网址
# 2.获取该网址的源码
# 3.使用正则表达式去匹配网址的源码（匹配所需要的数据类型）
# 4.将爬取的数据保存至本地或者数据库

# 确定要爬取数据的网址
url="https://www.ittime.com.cn/news/zixun.shtml"
# 该网址的源码(以该网页的原编码方式进行编码，特殊字符编译不能编码就设置ignore)
webSourceCode=urllib.request.urlopen(url).read().decode("utf-8","ignore")

# 匹配数据的正则表达式
# 所有的图片
imgRe=re.compile(r'src="(.*?\.jpg)"')
# 所有的标题
titleRe=re.compile(r'<h2><a href=".*?" target="_blank">(.*?)</a></h2>')
# 所有的简介
contentRe=re.compile(r'<p>(.*?)</p>')
# 所有的作者
authorRe=re.compile(r'<span class="pull-left from_ori">(.*?)<span class="year">(.*?)</span></span>')
# 匹配网页对应的标题数据
titles=titleRe.findall(webSourceCode)
images=imgRe.findall(webSourceCode)
content=contentRe.findall(webSourceCode)
authors=authorRe.findall(webSourceCode)
print("标题==============================================================")
for title in titles:
    print(title)
print("图片==============================================================")
for image in images:
    print("https://www.ittime.com.cn"+image)
print("内容简介==============================================================")
for c in content:
    print(c)
print("作者==============================================================")
for author in authors:
    print(author[0])
print("时间==============================================================")
for time in authors:
    print(author[1])






