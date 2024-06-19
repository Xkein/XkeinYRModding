
declare module "yr" {
    class Vector2D {
        X: number;
        Y: number;
    }
    class Vector3D {
        X: number;
        Y: number;
        Z: number;
    }
    class Vector4D {
        X: number;
        Y: number;
        Z: number;
        W: number;
    }
    class Matrix3D {

    }
    class Quaternion {
        X: number;
        Y: number;
        Z: number;
        W: number;
    }
    
    class CoordStruct extends Vector3D { }
    class CellStruct extends Vector2D { }
    class Point2D extends Vector2D { }

    class RectangleStruct {
        X: number;
        Y: number;
        Width: number;
        Height: number;
    }
}
