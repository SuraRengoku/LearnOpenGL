//
//  hdr.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 13.10.23.
//

#ifndef hdr_hpp
#define hdr_hpp

#include "shader.hpp"

int hdr();

#endif /* hdr_hpp */

/*
 存储帧缓冲时，亮度和颜色的值是默认被限制在0.0和1.0之间的。如果有一个特定区域，其中有多个亮光源氏这些数值综合超过了1.0，则需要hdr
 */

