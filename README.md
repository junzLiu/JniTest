# 防二次打包应用签名检测

JNI检测应用签名以防止二次打包带来的隐患

jni编译采用的实验性NDK构建插件 [Experimental Plugin use guide](http://tools.android.com/tech-docs/new-build-system/gradle-experimental)

Experimental Plugin 的使用可以看build.gradle文件和链接的说明

方案逻辑
- 获取Application
- 获取应用的签名信息
- 将签名信息MD5化
- 匹配签名信息是否相同
- 签名不同时在JNI_OnLoad 中返回 -1 使 App Crash掉
