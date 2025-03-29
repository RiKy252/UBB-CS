"use client";

import React, { createContext, useContext, useEffect, useState } from "react";
import { faker } from "@faker-js/faker";

const generateFakeTeams = (count: number): Team[] => {
  return Array.from({ length: count }, () => ({
    name: faker.company.name(),
    coachName: faker.name.fullName(),
    homeStadium: faker.company.name() + " Stadium",
    foundedYear: faker.number.int({ min: 1850, max: 2023 }),
    wins: faker.number.int({ min: 0, max: 20 }),
    draws: faker.number.int({ min: 0, max: 10 }),
    losses: faker.number.int({ min: 0, max: 20 }),
    goalsScored: faker.number.int({ min: 10, max: 80 }),
    goalsConceded: faker.number.int({ min: 10, max: 80 }),
    players: Array.from({ length: 11 }, () => faker.name.fullName()),
    country: faker.address.country(),
  }));
};

export interface Team {
  name: string;
  coachName: string;
  homeStadium: string;
  foundedYear: number;
  wins: number;
  draws: number;
  losses: number;
  goalsScored: number;
  goalsConceded: number;
  players: string[];
  country: string;
}

interface TeamsContextType {
  teams: Team[];
  setTeams: React.Dispatch<React.SetStateAction<Team[]>>;
}

const TeamsContext = createContext<TeamsContextType | undefined>(undefined);

export const TeamsProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [teams, setTeams] = useState<Team[]>([]);

  useEffect(() => {
    setTeams(generateFakeTeams(100));
  }, []);

  return (
    <TeamsContext.Provider value={{ teams, setTeams }}>
      {children}
    </TeamsContext.Provider>
  );
};

export const useTeams = (): TeamsContextType => {
  const context = useContext(TeamsContext);
  if (!context) {
    throw new Error("useTeams must be used within a TeamsProvider");
  }
  return context;
};