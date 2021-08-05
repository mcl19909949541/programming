from bs4 import  BeautifulSoup
import xlwt
import re

workbook = xlwt.Workbook(encoding="utf-8")
worksheet = workbook.add_sheet("sheet")
worksheet.write(0,0,"hello")
workbook.save("text01.xls")


