## Ubuntu下挂载第二块硬盘

自己组装了一个台式机，买不起正版windows，于是乎就装上ubuntu了。我有两块硬盘，一块是固态的，比较小；另一块是机械的，比较大。系统当然装在固态硬盘上。那么如何挂载那块机械硬盘呢？网上很多教程看了跟现实对照不上，比较扎心。摸索了一下，步骤如下：

### 第一步、查看

首先要查看一下系统识别出来的设备。也就是说，我希望知道，ubuntu到底发现了几块硬盘。用命令：lsblk

结果如下：
![](https://upload-images.jianshu.io/upload_images/24389525-083925eaea25bf3e.png?imageMogr2/auto-orient/strip|imageView2/2/w/621)
其中loop是什么鬼我也没搞清楚。总之，这个结果告诉我，我有两块硬盘：sda和nvme0n1。这两块硬盘各自有两个分区。其中，nvme0n1的两个分区都已经挂载，而sda的没有挂载。

### 第二步、找到sda

我们使用命令sudo fdisk -l可以看到有这么一段信息： 

![](https://upload-images.jianshu.io/upload_images/24389525-25b57b27f3020590.png?imageMogr2/auto-orient/strip|imageView2/2/w/627)

这段信息告诉我们sda以及它的两个分区在哪里（都在/dev/下）。

### 第三步、挂载（挂之前可以先将磁盘其格式化<windows上>）

我们新建一个目录/data，毕竟机械硬盘主要是为了作为数据盘的。我们以此作为挂载点。输入命令：sudo mount /dev/sda1 /data成功把sda1挂载到/data上。从此，/data就代表那块机械硬盘。

当然，你可以首先对该硬盘进行一些分区设置，比如删除分区或者新建分区，然后再挂载。使用sudo fdisk /dev/sda命令进行设置。输入该命令之后有详细的帮助文档指导操作。不过切记：操作完成之后要格式化，只有格式化之后才可以挂载。否则会提示下面的错误：mount: /data: wrong fs type, bad option, bad superblock on /dev/sda, missing codepage or helper program, or other error.

格式化的命令是：sudo mkfs -t ext4 /dev/sda。

现在，再次lsblk，你会发现硬盘已经成功挂载上了：
![](https://upload-images.jianshu.io/upload_images/24389525-ad55d3aa6b82d04c.png?imageMogr2/auto-orient/strip|imageView2/2/w/609)

#### 第四步、修改分区文件/etc/fstab（没有配置此步骤）

上面的步骤还不够，你会发现：重启之后，硬盘又不见了。你需要修改/etc/fstab文件，确保重启之后挂载依然有效。这个文件的格式如下：

![](https://upload-images.jianshu.io/upload_images/24389525-fd100d5ff1e56cef.png?imageMogr2/auto-orient/strip|imageView2/2/w/723)
也就是，要填写file system、mount point、type、options、dump、pass等六项。其中mount point为我们的挂载点/data/；type为我们格式化的文件格式，ext4；options我们一般就是defaults；dump都是0、pass也都是0，除非挂载点是/。我们唯一需要动脑筋的是UUID。使用命令：sudo blkid /dev/sda来获得UUID：

/dev/sda: UUID="f1d9a15d-243b-4d91-8b3f-160782c1acab" TYPE="ext4"

因此，我们在fstab文件下添加一行：

UUID=f1d9a15d-243b-4d91-8b3f-160782c1acab  /data/    ext4    defaults    0    0

保存退出。用sudo mount -a测试一下。