# LearnOpenGL
## 经历过一次迭代，在lightingmaps文件之后的程序均需要替换loadTexture函数才能运行，该函数在general.h中定义
## Note: after the lastest reconstruction, all programs behind file "lightingmaps" shall run well after replacing function "loadTexture", which is defined in "general.h"

## BUGs:
### 在进行blinn-phong和phong两种光照模型的渲染切换时，会由于切换按键B的击发时间不同而跨越1个或以上主循环，这可能导致切换不成功
