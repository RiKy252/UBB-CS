using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Linq;

namespace rt;

public class CtScan: Geometry
{
    private readonly Vector _position;
    private readonly double _scale;
    private readonly ColorMap _colorMap;
    private readonly byte[] _data;

    private readonly int[] _resolution = new int[3];
    private readonly double[] _thickness = new double[3];
    private readonly Vector _v0; // bottom-left-bakc corner
    private readonly Vector _v1; // top-right-front corner

    public CtScan(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap) : base(Color.NONE)
    {
        _position = position;
        _scale = scale;
        _colorMap = colorMap;

        var lines = File.ReadLines(datFile);
        foreach (var line in lines)
        {
            var kv = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
            if (kv[0] == "Resolution")
            {
                _resolution[0] = Convert.ToInt32(kv[1]);
                _resolution[1] = Convert.ToInt32(kv[2]);
                _resolution[2] = Convert.ToInt32(kv[3]);
            } else if (kv[0] == "SliceThickness")
            {
                _thickness[0] = Convert.ToDouble(kv[1]);
                _thickness[1] = Convert.ToDouble(kv[2]);
                _thickness[2] = Convert.ToDouble(kv[3]);
            }
        }

        _v0 = position;
        _v1 = position + new Vector(_resolution[0]*_thickness[0]*scale, _resolution[1]*_thickness[1]*scale, _resolution[2]*_thickness[2]*scale);

        var len = _resolution[0] * _resolution[1] * _resolution[2];
        _data = new byte[len];
        using FileStream f = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
        if (f.Read(_data, 0, len) != len)
        {
            throw new InvalidDataException($"Failed to read the {len}-byte raw data");
        }
    }
    
    private ushort Value(int x, int y, int z)
    {
        if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2])
        {
            return 0;
        }

        return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
    }

    public override Intersection GetIntersection(Line line, double minDist, double maxDist)
    {
        // Ray-box intersection using slab method
        Vector dir = line.Dx;
        
        // from wikipedia: Each pair of parallel planes defines a slab
        // and the volume contained in the box is the intersection of the three slabs

        // v0 and v1 -> entry and exit points of bounding box
        // X-axis slab: planes at _v0.X and _v1.X
        double tx1 = (_v0.X - line.X0.X) / dir.X;
        double tx2 = (_v1.X - line.X0.X) / dir.X;

        // Y-axis slab: planes at _v0.Y and _v1.Y
        double ty1 = (_v0.Y - line.X0.Y) / dir.Y;
        double ty2 = (_v1.Y - line.X0.Y) / dir.Y;

        // Z-axis slab: planes at _v0.Z and _v1.Z
        double tz1 = (_v0.Z - line.X0.Z) / dir.Z;
        double tz2 = (_v1.Z - line.X0.Z) / dir.Z;

        // Find intersection of all three slabs:
        // tStart = latest entry, tEnd = earliest exit
        // (enterning all slabs)      (leaving any slab)
        double tStart = Math.Max(
            Math.Min(tx1, tx2), 
            Math.Max(
                Math.Min(ty1, ty2),
                Math.Min(tz1, tz2)
            )
        );
        double tEnd = Math.Min(
            Math.Max(tx1, tx2),
            Math.Min(
                Math.Max(ty1, ty2),
                Math.Max(tz1, tz2)
            )
        );

        if (tEnd < tStart) return Intersection.NONE;

        // Clamp to distance bounds
        // Where the ray enters / exits the bounding box
        tStart = Math.Max(tStart, minDist);
        tEnd = Math.Min(tEnd, maxDist);
        if (tEnd < tStart) return Intersection.NONE;

        // Initialize accumulation variables
        // small enough step size so we dont miss details (half the smallest voxel dimension)
        double step = Math.Min(Math.Min(_thickness[0], _thickness[1]), _thickness[2]) * _scale * 0.5;
        var firstTIntersection = 0.0;

        // Computing color of the material by accumulation (front-to-back)
        var accumColor = new Color();
        double accumAlpha = 0.0;
        bool found = false;
        Vector firstNormal = null;

        // March through volume
        for (double t = tStart; t <= tEnd; t += step)
        {
            var currentPos = line.CoordinateToPosition(t);
            // Check the point to be inside the volume
            if (currentPos.X >= _v0.X && currentPos.X <= _v1.X &&
                currentPos.Y >= _v0.Y && currentPos.Y <= _v1.Y &&
                currentPos.Z >= _v0.Z && currentPos.Z <= _v1.Z)
            {
                var pointColor = GetColor(currentPos);
                if (pointColor.Alpha == 0) continue;

                // Getting the normal at the first intersection
                if (!found)
                {
                    firstTIntersection = t;
                    firstNormal = GetNormal(currentPos);
                    found = true;
                }
                // Beer-Lambert Law to calculate density
                double density = pointColor.Alpha;
                double pointAlphaContribution = density * 0.4;

                // Calculate color
                double remainingTransparency = 1.0 - accumAlpha;
                double actualContribution = pointAlphaContribution * remainingTransparency;

                accumColor += pointColor * actualContribution;
                accumAlpha += actualContribution;
            }
        }

        if (found && accumAlpha > 0.05) {

            // Volume material
            var volumeMaterial = new Material(
                new Color(0.1, 0.1, 0.1, 1.0),
                new Color(0.4, 0.4, 0.4, 1.0),
                new Color(0.7, 0.7, 0.7, 1.0),
                100
            );

            return new Intersection(
                true,                    // valid
                true,                    // visible
                this,                    // geometry
                line,                    // ray
                firstTIntersection,      // intersection parameter
                firstNormal,             // surface normal
                volumeMaterial,          // material
                accumColor * accumAlpha  // color
            );
        }
        return Intersection.NONE;
    }
    
    private int[] GetIndexes(Vector v)
    {
        return new []{
            (int)Math.Floor((v.X - _position.X) / _thickness[0] / _scale), 
            (int)Math.Floor((v.Y - _position.Y) / _thickness[1] / _scale),
            (int)Math.Floor((v.Z - _position.Z) / _thickness[2] / _scale)};
    }
    private Color GetColor(Vector v)
    {
        int[] idx = GetIndexes(v);
    
        ushort value = Value(idx[0], idx[1], idx[2]);
        return _colorMap.GetColor(value);
    }

    private Vector GetNormal(Vector v)
    {
        int[] idx = GetIndexes(v);
        double x0 = Value(idx[0] - 1, idx[1], idx[2]);
        double x1 = Value(idx[0] + 1, idx[1], idx[2]);
        double y0 = Value(idx[0], idx[1] - 1, idx[2]);
        double y1 = Value(idx[0], idx[1] + 1, idx[2]);
        double z0 = Value(idx[0], idx[1], idx[2] - 1);
        double z1 = Value(idx[0], idx[1], idx[2] + 1);

        return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
    }
}