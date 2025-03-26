"use client"
import { cloneElement, ReactElement, useState } from "react";
import "./globals.css";
import React from "react";
import { TeamsProvider } from "./TeamContext";

export default function RootLayout({ children }: { children: React.ReactNode }) {
  return (
    <html lang="en">
      <body className="bg-gray-100">
        <TeamsProvider>
        <main className="container mx-auto p-4">
          {children}
        </main>
        </TeamsProvider>
      </body>
    </html>
  );
}

