
from bs4 import BeautifulSoup
import re
import urllib.request,urllib.error
import xlwt

def main():
    #初始网址
    baseurl = "https://movie.douban.com/top250?start="
    
    datalist =getData(baseurl)
    #保存路径
    for data in datalist:
        print(data)
    savepath = "douban250.xls"
    #保存
    saveData(datalist,savepath)
    
#影片链接规则
findLink = re.compile(r'<a href="(.*?)">')#创建正则表达式规则
#影片图片链接规则
findImgSic = re.compile(r'<img.*src="(.*?)"',re.S)  #re.S 让换行符包含在字符串中
#影片片名
findTitle = re.compile(r'<span class="title">(.*)</span>')
#影片评分
findRating = re.compile(r'<span class="rating_num" property="v:average">>(.*)</span>')
#评价人数
findJudge = re.compile(r'<span>(\d*)')
#找到概况
findIng = re.compile(r'"inq">(.*)</span>')
#找到相关内容
findBd = re.compile(r'<p class="">(.*?)</p>',re.S)

#爬取网址
def getData(baseurl):
    datalist = []
    for i in range(0,10):   #调用获取网页的函数10次
        url = baseurl + str(i*25)
        html = askURL(url)   #保存获取的网页信息
        
        
        #逐一解析
        soup = BeautifulSoup(html,"html.parser")
        for item in soup.find_all('div',class_="item"):  #查找字符串
            data = []   #保存一部电影的所有信息
            item = str(item)
            #print(item)
            
            Link = re.findall(findLink,item)[0]   #查找影片链接
            data.append(Link)
            
            imgSrc = re.findall(findImgSic,item)[0]  
            data.append(imgSrc)   #匹配添加图片
            
            titles = re.findall(findTitle,item)  
            if(len(titles)==2):
               
                ctitle = titles[0]
                data.append(ctitle)
               
                otitle = titles[1].replace("/","")  
                data.append(otitle)
            else :
                data.append(titles[0])
                data.append('  ')  #外国名留空
            
            rating =re.findall(findRating,item)
            data.append(rating)
            
            judgeNum = re.findall(findJudge,item)
            data.append(judgeNum)
            
            inq = re.findall(findIng,item)
            if len(inq) !=0:
                inq = inq[0].replace(",","")
                data.append(inq)
            else :
                data.append("  ")
                
            bd = re.findall(findBd,item)[0]
            bd = re.sub('br(\s+)?/>(\s+)?'," ",bd)
            bd = re.sub('/'," ",bd)
            data.append(bd.strip())
            
            datalist.append(data)  #把处理好的一部电影信息存储

    #print(datalist)
    return datalist

def saveData(datalist,savepath):
    book = xlwt.Workbook(encoding="utf-8")
    sheet  =book.add_sheet('douban250',cell_overwrite_ok=True)
    col = ('Link to film details','Image links','Chinese Name of Movie','Foreign Name of Movie','score','Judgingnum','General situation ','The relevant information')
    for i in range(0,8):
        sheet.write(0,i,col[i])
    for i in range(0,250):
        print("%d条"%i)
        data = datalist[i]
        for j in range(0,8):
            sheet.write(i+1,j,data[j])
            
    book.save('student.xls')
def askURL(url):
    head = {
    "User-Agent":" Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.25 Safari/537.36 Core/1.70.3861.400 QQBrowser/10.7.4313.400"
        }
    request = urllib.request.Request(url,headers = head)
    html = ""
    try:
            response = urllib.request.urlopen(request)
            html = response.read().decode("utf-8")
            #print(html)
    except urllib.error.URLError as e:
            if hasattr(e,"code"):
                print(e.code)
            if hasattr(e,"reason"):
                print(e.reason)
    return html
   

    
if __name__ == "__main__":
    main()
