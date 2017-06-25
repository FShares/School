'''
定义Account类
'''
class Account(object):
    #(Uname,Upass,URname,USex)
    uname = ""
    uPass = ""
    uRame = ""
    uSex = ""
    uBalance = ""
    # 实例初始化 带参构造函数
    def __init__(self,uname,uPass,uRname,uSex,uBalance):
        self.uname = uname
        self.uPass = uPass
        self.uRame = uRname
        self.uSex = uSex
        self.uBalance = uBalance