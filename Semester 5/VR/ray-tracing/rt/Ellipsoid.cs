using System;

namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }
        
        public Quaternion Rotation { get; set;  } = Quaternion.NONE;
        
        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid (Ellipsoid e) : this(new Vector(e.Center), new Vector(e.SemiAxesLength), e.Radius, new Material(e.Material), new Color(e.Color))
        {
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // To rotate the ellipsoid, we rotate the ray in the opposing direction
            // this will keep the ellipsoid in a canonical axis-aligned orientation

            // Inverse rotation
            Quaternion invRotation = Rotation.Inverse();
            // Get origin
            Vector o = line.X0 - Center;
            Vector o_r = new Vector(o);
            // Rotate origin
            o_r.Rotate(invRotation);
            // Rotate direction of the ray
            Vector d_r = new Vector(line.Dx);
            d_r.Rotate(invRotation);

            // Make it a sphere, by dividing the coordinates with the elipsoid axis (unit sphere)
            Vector o_s = new Vector(o_r.X / SemiAxesLength.X,
                                  o_r.Y / SemiAxesLength.Y,
                                  o_r.Z / SemiAxesLength.Z);
            
            Vector d_s = new Vector(d_r.X / SemiAxesLength.X,
                                  d_r.Y / SemiAxesLength.Y,
                                  d_r.Z / SemiAxesLength.Z);

            // Sphere-Ray intersection
            // Solve quadratic equation, interpret result
            double a = d_s.Length2();
            double b = 2 * (o_s * d_s); 
            double c = o_s.Length2() - Radius * Radius;

            // delta
            double disc = b * b - 4 * a * c;
            // They dont intersect
            if (disc < 0) return Intersection.NONE;

            // They intersect, we must check if it's visible
            double sqrtDisc = Math.Sqrt(disc);
            double inv2a = 1.0 / (2 * a);
            // t1 the entry point
            double t1 = (-b - sqrtDisc) * inv2a;
            // t2 the exit point
            double t2 = (-b + sqrtDisc) * inv2a;

            double t = double.PositiveInfinity;
            bool visible = false;

            // Closest valid intersection
            if (t1 >= minDist && t1 <= maxDist) { t = t1; visible = true; }
            else if (t2 >= minDist && t2 <= maxDist) { t = t2; visible = true; }

            if (!visible) return Intersection.NONE;
            
            // We have an intersection, we calculate the normal vector to transform it back
            Vector p_s = o_s + d_s * t; // intersection point in sphere space

            Vector normal = new Vector(p_s.X / SemiAxesLength.X,
                                       p_s.Y / SemiAxesLength.Y,
                                       p_s.Z / SemiAxesLength.Z);
            // and rotate back
            normal.Rotate(Rotation);
            normal.Normalize();
            
            var material = Material.FromColor(Color);
            return new Intersection(true, true, this, line, t, normal, material, Color);
        }
    }
}
