#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 vsPos;

void main()
{
    // 解释为什么左下角是黑的
    // 左下角是负数，所以是黑色
    // 而颜色只有 0-1
    // test push
    FragColor = vec4(vsPos, 1.0);
}