using System;

namespace rt;

public class Quaternion(double w, double x, double y, double z)
{
    public static readonly Quaternion NONE = new(0, 1, 0, 0);
    public double W { get; set; } = w; // rotation angle (scalar)
    public double X { get; set; } = x; // vectorial part (x,y,z) -> axis of rotation
    public double Y { get; set; } = y;
    public double Z { get; set; } = z;

    public Quaternion Normalize()
    {
        var a = Math.Sqrt(W * W + X * X + Y * Y + Z * Z);
        W /= a;
        X /= a;
        Y /= a;
        Z /= a;
        return this;
    }
    
    public Quaternion Inverse()
    {
        return new Quaternion(W, -X, -Y, -Z);
    }
    
    public static Quaternion FromAxisAngle(double aa, Vector axis)
    {
        double halfAngle = -aa / 2.0;
        double sinHalfAngle = Math.Sin(halfAngle);
        
        return new Quaternion(
            Math.Cos(halfAngle),
            axis.X * sinHalfAngle,
            axis.Y * sinHalfAngle,
            axis.Z * sinHalfAngle
        ).Normalize();
    }
}