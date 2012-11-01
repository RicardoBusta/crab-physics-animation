#ifndef PROP_H
#define PROP_H

class Scene;
class Material;

enum PROP_TYPE{PROP_PLANE};

class Prop
{
public:
    Prop(Scene *scene, PROP_TYPE type);
    ~Prop();

    void draw();

    Material *mat;

    Scene *scene;
    PROP_TYPE type;
};

#endif // SCENEPROP_H
