
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
        constructor(col1 : Vector3D, col2 : Vector3D, col3 : Vector3D, col4 : Vector3D);
        constructor(m00 : number, m01 : number, m02 : number, m03 : number, m10 : number, m11 : number, m12 : number, m13 : number, m20 : number, m21 : number, m22 : number, m23 : number);
        MakeIdentity() : void;
        Translate(x : number, y : number, z : number) : void;
        Translate(vec : Vector3D) : void;
        TranslateX(x : number) : void;
        TranslateY(y : number) : void;
        TranslateZ(z : number) : void;
        Scale(x : number, y : number, z : number) : void;
        Scale(factor : number) : void;
        ScaleX(factor : number) : void;
        ScaleY(factor : number) : void;
        ScaleZ(factor : number) : void;
        ShearYZ(y : number, z : number) : void;
        ShearXY(x : number, y : number) : void;
        ShearXZ(x : number, z : number) : void;
        PreRotateX(theta : number) : void;
        PreRotateY(theta : number) : void;
        PreRotateZ(theta : number) : void;
        RotateX(theta : number) : void;
        RotateX(Sin : number, Cos : number) : void;
        RotateY(theta : number) : void;
        RotateY(Sin : number, Cos : number) : void;
        RotateZ(theta : number) : void;
        RotateZ(Sin : number, Cos : number) : void;
        static FromQuaternion(quat : Quaternion) : Matrix3D;
        ToQuaternion() : Quaternion;
        ApplyQuaternion(quat : Quaternion) : void;
        static GetIdentity() : Matrix3D;
        
        Data: any;
        Row: any;
        row: any;
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

    class ColorStruct {
        constructor(r : number, g : number, b : number);
        R: number;
        G: number;
        B: number;
    }
}
