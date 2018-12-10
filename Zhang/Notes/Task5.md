# 任务5 #
### 1.Github访问速度慢和下载慢的解决方法 ###

#### 原因 ####
``` Github的CDN被墙，由于网络代理商的原因，所以访问下载很慢。```

#### 解决方法 ####
``` 绕过DNS解析，从本地直接绑定host。```

#### 具体解决过程 ####
在本地host文件中添加映射
Windows系统的host文件位置如下：
```C:\Windows\System32\drives\etc\hosts```

Mac\Linux系统的hosts文件位置如下：
```/etc/hosts```

具体步骤如下：

```
1.用文本编辑器打开hosts文件
2.访问ipaddress网站https://www.ipaddress.com/，查看网站对应的IP地址，输入网址则可查阅到对应的IP地址，这是一个查询域名映射关系的工具
3.查询 github.global.ssl.fastly.net 和 github.com 两个地址
4.多查几次，选择一个稳定，延迟较低的 ip 按如下方式添加到host文件的最后面
5.保存hosts文件
6.重启浏览器，或刷新DNS缓存，告诉电脑hosts文件已经修改，linux/mac执行sudo /etc/init.d/networking restart命令；windows在cmd中输入ipconfig /flushdns命令即可。
7.起飞！！！
```
### 2.Git里面的origin含义 ###
程序员的代码库(repository)可以存放在本地电脑中或托管到Github的服务器上。
在默认情况下，origin指向的是本地的代码库托管在Github上的版本。
假设首先在Github上创建了一个Repository，叫做repository，用户Github ID是user1，这个时候指向用户的代码库链接是
```https://github.com/user1/repository```

如果用户在Terminal中输入
```git clone https://github.com/user1/repository```

那么git就会在本地拷贝一份托管到Github上的代码库。
这时用户cd到repository，然后输入
```git remote -v```

能够看到控制台输出
```
origin https://github.com/user1/repository.git (fetch)
origin https://github.com/user1/repository.git (push)
```
即git为用户默认创建了一个指向远端代码库的origin，从该地址clone下来。
再假设现在有某个用户user2 fork了user1的repository，则它的代码库链接为
```https://github.com/user2/repository```
如果用户2执行clone操作，在控制台输入
```git remote -v```
则看到输出
```
origin https://github.com/user2/repository.git (fetch)
origin https://github.com/user2/repository.git (push)
```
此时origin指向的位置是user2的远程代码库。
这个时候，如果user2想要加入一个远程指向user1的代码库，它可以在控制台输入
```git remote add upstream https://github.com/user1/repository.git```

然后再输入
```git remote -v```
输出结果为
```
origin https://github.com/user2/repository.git (fetch)
origin https://github.com/user2/repository.git (push)
upstream https://github.com/user1/repository.git (push)
upstream https://github.com/user1/repository.git (push)
```
就增加了对user1代码库的upstream，也就是之前对指向位置的命名。

**综上所述，origin是“本体”，是用户clone一个托管在Github上的代码库时，git默认创建的指向这个远程代码库的标签。**
