LABEL FACE
==========

该工具用于在人脸上标记 5 个关键点（左眼、右眼、鼻尖、左嘴角，和右嘴角，最重要的，***按顺序***！）。

## 编译
需要安装 `Opencv 2.4`，如果没有，在 `Ubuntu` 上可以通过下面方法安装：

```bash
sudo apt-get install libopencv-dev
```

在代码目录输入
```bash
make
```
编译。

## 使用

```bash
./label_face $idx $folder
```

`$idx` 是你当前操作的起始点，从 `$folder` 文件夹第 `$idx` 个文件开始操作。当然这样子坐标是会被输出到 `stdout` 的，
所以你需要重新定向到制定的文件，存储坐标，比如：

```bash
./label_face 0 faces >> landmark-file
```

`>>` 是 `append` 模式的意思，避免覆盖你之前的工作进度。你完全可以做了一半，然后去看看百度贴吧，然后再回来做一会。

![Example](pics/example-2.png)

打开程序之后，你只需要点击关键点即可。选取完毕之后，你只需要按下 `f`，就可以保存进度，如果你觉得你刚刚手抖了标错了
一个点，你可以按下 `d` 键回退。如果你觉得有些厌烦了，你可以按下 `q` 暂停工作进度，你当前的工作会被保存在你之前制定
的文件中（***小心操作，注意不要误删***）。
