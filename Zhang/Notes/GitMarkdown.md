## 命令行中常用的Git指令 ##

### 1.安装Git ### 

```
$ sudo apt-get install git
```

### 2.生成ssh秘钥 ###

```
$ ssh-keygen -t rsa -C "your@email.com"
```

### 3.使用Git命令下载GitHub上的项目 ###

```
$ git clone XXX/XXX.git

注：对于本实验室的项目，命令行指定为  

$ git clone git@github.com:DML308/costream.org.git
$ git clone git@github.com:DML308/cn.costream.org.git

```

### 4.使用Git指令对clone到本地仓库的代码进行修改&提交  ###

```
$ add -A
$ git commit -m "your comment" 
$ git pull #拉取别人修改的代码,无冲突时默认合并
$ git push
```

### 5.Git版本回滚 ###

```
$ git reset --hard
```

~~什么是 Pull Request?~~

~~用类比的方法来解释一下 pull reqeust。想想我们中学考试，老师改卷的场景吧。你做的试卷就像仓库，你的试卷肯定会有很多错误，就相当于程序里的 bug。老师把你的试卷拿过来，相当于先 fork。在你的卷子上做一些修改批注，相当于 git commit。最后把改好的试卷给你，相当于发 pull request，你拿到试卷重新改正错误，相当于 merge。当你想更正别人仓库里的错误时，要走一个流程：先 fork 别人的仓库，相当于拷贝一份，相信我，不会有人直接让你改修原仓库的clone 到本地分支，做一些 bug fix发起 pull request 给原仓库，让他看到你修改的 bug原仓库 review 这个 bug，如果是正确的话，就会 merge 到他自己的项目中至此，整个 pull request 的过程就结束了。~~
