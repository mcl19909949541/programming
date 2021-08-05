import scrapy


class ItcastSpider(scrapy.Spider):
    name = 'itcast'
    allowed_domains = ['itcast.cn']
    start_urls = ['http://www.itcast.cn/channel/teacher.shtml',]

    def parse(self, response):
        filemane = "teaacher.html"
        open(filemane,'w').write(response.body)
        pass
