from flask import Flask, render_template
import pandas as pd
app = Flask(__name__)



@app.route("/")
def show():
    #读取csv文件内容发送到html中即可
    #这里不知道为什么要用绝对路径才行，而且python的绝对路径是r'\ \'或’\\ \\‘这样的
    data = pd.read_csv(r"C:\Users\POG\Desktop\编程\#python_work\movie\data.csv")
    #替换内容
    data = data.rename(columns={"3":"name","2":"value"})
    #先替换再变成list，不能反过来
    data = data.to_dict(orient="records")
    #这里要把data.csv文件中的3，2对齐而且不能有空格
    print(data)

    return render_template('show.html',data = data)


if __name__ == '__main__':
    app.run(debug=True)
