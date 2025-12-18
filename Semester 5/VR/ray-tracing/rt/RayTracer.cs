using System;

namespace rt
{
    class RayTracer(Geometry[] geometries, Light[] lights)
    {
        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            return -n * viewPlaneSize / imgSize + viewPlaneSize / 2;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist, bool ignoreCtScan = false)
        {
            var intersection = Intersection.NONE;

            foreach (var geometry in geometries)
            {
                if (ignoreCtScan && geometry is CtScan)
                    continue;

                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if (intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }

        // Cast a shadow ray from slightly offset point towards the light and see if anything blocks it
        private bool IsLit(Vector point, Light light)
        {
            // Calculating light direction and distance
            Vector lightDirection = light.Position - point;
            double lightDistance = lightDirection.Length();
            lightDirection.Normalize();

            // Get an offset (to prevent self-shadowing)
            Vector offsetPoint = point + lightDirection * 0.001;
            // Cast a shadow ray
            Line shadowRay = new Line(offsetPoint, light.Position);

            // Check for obstructions
            var shadowIntersection = FindFirstIntersection(shadowRay, 0.001, lightDistance - 0.001, true);

            return !shadowIntersection.Valid;
        }
        public void Render(Camera camera, int width, int height, string filename)
            {
                var background = new Color(0.2, 0.2, 0.2, 1.0);

                var image = new Image(width, height);

                // Setup camera frame
                camera.Normalize();

                Vector cameraForward = new Vector(camera.Direction);
                Vector cameraUp = new Vector(camera.Up);
                Vector cameraRight = cameraUp ^ cameraForward;
                cameraRight.Normalize();

                Vector viewPlaneCenter = camera.Position + cameraForward * camera.ViewPlaneDistance;

                for (var i = 0; i < width; i++)
                {
                    for (var j = 0; j < height; j++)
                    {
                        // For each pixel, we convert the pixel to the world ray
                        // 3d ray (from camera through the view plane)
                        double x = ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                        double y = ImageToViewPlane(j, height, camera.ViewPlaneHeight);
                        Vector viewPlanePoint = viewPlaneCenter + cameraRight * x + cameraUp * y;
                        Line ray = new Line(camera.Position, viewPlanePoint);

                        // Find closest intersection tracing the ray through the scene
                        var intersection = FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance);

                        // Calculate pixel color (or use background if no intersection)
                        Color pixelColor = background;
                        if (intersection.Valid && intersection.Visible)
                        {
                            pixelColor = CalculateColor(intersection);
                        }
                        image.SetPixel(i, j, pixelColor);
                    }
                }

                image.Store(filename);
            }

            private Color CalculateColor(Intersection intersection)
            {
                // Phong lighting model (ambient, diffuse, specular lights)
                Color finalColor = new Color(0, 0, 0, 1);

                foreach (var light in lights)
                {
                    if (IsLit(intersection.Position, light))
                    {
                        // Ambient (always present) -> material's ambient + light's ambient
                        Color ambient = intersection.Material.Ambient * light.Ambient;

                        // T = (L - v).normalize()
                        Vector lightDirection = light.Position - intersection.Position;
                        lightDirection.Normalize();
                        double diffuseFactor = Math.Max(0, intersection.Normal * lightDirection);
                        // Diffuse = material diffuse * light diffuse * max(0, N*L) (angle between them)
                        Color diffuse = intersection.Material.Diffuse * light.Diffuse * diffuseFactor;

                        // Specular depends on the viewing angle:
                        // R = N * (N*T) * 2 - T
                        Vector viewDirection = intersection.Line.X0 - intersection.Position; // 
                        viewDirection.Normalize();
                        Vector reflectionDirection = intersection.Normal * (2 * (intersection.Normal * lightDirection)) - lightDirection;
                        reflectionDirection.Normalize();

                        // color += m.sp * l.sp * ((R * T) ^ m.sh)
                        double specularFactor = Math.Max(0, viewDirection * reflectionDirection);
                        specularFactor = Math.Pow(specularFactor, intersection.Material.Shininess);
                        Color specular = intersection.Material.Specular * light.Specular * specularFactor;

                        finalColor = finalColor + ambient + diffuse + specular;
                    }
                    else
                    {
                        // Light doesn't hit geometry, apply only ambient color
                        Color ambient = intersection.Material.Ambient * light.Ambient;
                        finalColor = finalColor + ambient;
                    }
                }

                finalColor = finalColor * intersection.Color;

                return finalColor;
            }
    }
}