
declare module "YRpp" {
    class Vector2D {
        constructor(x : number, y : number);
        X: number;
        Y: number;
        Magnitude() : number;
        MagnitudeSquared() : number;
        DistanceFrom(a: Vector2D) : number;
        DistanceFromSquared(a: Vector2D) : number;
        IsCollinearTo(a: Vector2D) : boolean;
        FindScalar(a: Vector2D) : number;
        op_Addition(a: Vector2D) : Vector2D;
        op_Subtraction(a: Vector2D) : Vector2D;
        op_Equality(a: Vector2D) : boolean;
        op_Inequality(a: Vector2D) : boolean;
        op_Multiply(r: number) : Vector2D;
        op_Multiply(a: Vector2D) : number;
    }
    class Vector3D {
        constructor(x : number, y : number, z : number);
        X: number;
        Y: number;
        Z: number;
        Magnitude() : number;
        MagnitudeSquared() : number;
        DistanceFrom(a: Vector3D) : number;
        DistanceFromSquared(a: Vector3D) : number;
        IsCollinearTo(a: Vector3D) : boolean;
        FindScalar(a: Vector3D) : number;
        CrossProduct(a: Vector3D) : Vector3D;
        op_Addition(a: Vector3D) : Vector3D;
        op_Subtraction(a: Vector3D) : Vector3D;
        op_Equality(a: Vector3D) : boolean;
        op_Inequality(a: Vector3D) : boolean;
        op_Multiply(r: number) : Vector3D;
        op_Multiply(a: Vector3D) : number;
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
