import type { NextConfig } from "next";
import type { Configuration } from "webpack";

const nextConfig: NextConfig = {
  webpack: (config: Configuration, { isServer }) => {
    if (isServer) {
      // Ensure externals is an array
      if (!Array.isArray(config.externals)) {
        config.externals = config.externals ? [config.externals] : [];
      }

      // config.externals.push("pg");
    }
    return config;
  },
};

export default nextConfig;
