// app/types/team.ts
export interface TeamMetadata {
  isMostWins?: boolean;
  isLeastWins?: boolean;
  isAvgWins?: boolean;
}

export interface TeamType {
  id: number;
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
  position?: number;
  gamesPlayed?: number;
  points?: number;
  metadata?: TeamMetadata;
  createdAt?: Date;
  updatedAt?: Date;
}