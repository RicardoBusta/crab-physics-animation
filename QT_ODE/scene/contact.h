#ifndef CONTACT_H
#define CONTACT_H

class Material;
class Matrix4f;

class Contact
{
public:
    Contact(float x, float y, float z);
    ~Contact();

    Material *mat;
    Matrix4f *tr;

    void draw();
};

#endif // CONTACT_H
