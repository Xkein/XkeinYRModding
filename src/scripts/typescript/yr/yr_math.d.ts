
declare module "YRpp" {
    class Vector2D {
        constructor(x : number, y : number);
        X: number;
        Y: number;
    }
    class Vector3D {
        constructor(x : number, y : number, z : number);
        X: number;
        Y: number;
        Z: number;
    }
    class Vector4D {
        constructor(x : number, y : number, z : number, w : number);
        X: number;
        Y: number;
        Z: number;
        W: number;
    }
    class Matrix3D {

    }
    class Quaternion {
        constructor(x : number, y : number, z : number, w : number);
        X: number;
        Y: number;
        Z: number;
        W: number;
    }
    
    class CoordStruct extends Vector3D { }
    class CellStruct extends Vector2D { }
    class Point2D extends Vector2D { }
    class BulletVelocity extends Vector3D { }

    class RectangleStruct {
        X: number;
        Y: number;
        Width: number;
        Height: number;
    }
}
