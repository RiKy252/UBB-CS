
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

export interface RankedTeam extends Team {
  gamesPlayed: number;
  position: number;
  points: number;
  metadata?: {
    isMostWins: boolean;
    isLeastWins: boolean;
    isAvgWins: boolean;
  }
}

let teams: Team[] = [
  {
    name: "Arsenal",
    coachName: "Mikel Arteta",
    homeStadium: "Emirates Stadium",
    foundedYear: 1886,
    wins: 18,
    draws: 6,
    losses: 4,
    goalsScored: 60,
    goalsConceded: 30,
    players: [
      "Bukayo Saka",
      "Martin Ødegaard",
      "Gabriel Jesus",
    ],
    country: "England",
  },
  {
    name: "Aston Villa",
    coachName: "Unai Emery",
    homeStadium: "Villa Park",
    foundedYear: 1874,
    wins: 16,
    draws: 5,
    losses: 7,
    goalsScored: 55,
    goalsConceded: 35,
    players: [
      "Ollie Watkins",
      "Emiliano Buendía",
      "Philippe Coutinho",
    ],
    country: "England",
  },
  {
    name: "Bournemouth",
    coachName: "Andoni Iraola",
    homeStadium: "Vitality Stadium",
    foundedYear: 1899,
    wins: 8,
    draws: 6,
    losses: 14,
    goalsScored: 35,
    goalsConceded: 45,
    players: [
      "Dominic Solanke",
      "Marcus Tavernier",
      "Philip Billing",
    ],
    country: "England",
  },
  {
    name: "Brentford",
    coachName: "Thomas Frank",
    homeStadium: "Gtech Community Stadium",
    foundedYear: 1889,
    wins: 12,
    draws: 9,
    losses: 7,
    goalsScored: 40,
    goalsConceded: 39,
    players: [
      "Ivan Toney",
      "Bryan Mbeumo",
      "Christian Nørgaard",
    ],
    country: "England",
  },
  {
    name: "Brighton & Hove Albion",
    coachName: "Roberto De Zerbi",
    homeStadium: "Amex Stadium",
    foundedYear: 1901,
    wins: 15,
    draws: 7,
    losses: 6,
    goalsScored: 50,
    goalsConceded: 35,
    players: [
      "Leandro Trossard",
      "Pascal Groß",
      "Moisés Caicedo",
    ],
    country: "England",
  },
  {
    name: "Chelsea",
    coachName: "Graham Potter",
    homeStadium: "Stamford Bridge",
    foundedYear: 1905,
    wins: 10,
    draws: 5,
    losses: 12,
    goalsScored: 45,
    goalsConceded: 40,
    players: [
      "Kai Havertz",
      "Raheem Sterling",
      "Mason Mount",
    ],
    country: "England",
  },
  {
    name: "Crystal Palace",
    coachName: "Patrick Vieira",
    homeStadium: "Selhurst Park",
    foundedYear: 1905,
    wins: 9,
    draws: 8,
    losses: 11,
    goalsScored: 38,
    goalsConceded: 42,
    players: [
      "Wilfried Zaha",
      "Eberechi Eze",
      "Michael Olise",
    ],
    country: "England",
  },
  {
    name: "Everton",
    coachName: "Frank Lampard",
    homeStadium: "Goodison Park",
    foundedYear: 1878,
    wins: 7,
    draws: 5,
    losses: 15,
    goalsScored: 30,
    goalsConceded: 50,
    players: [
      "Dominic Calvert-Lewin",
      "Anthony Gordon",
      "Amadou Onana",
    ],
    country: "England",
  },
  {
    name: "Fulham",
    coachName: "Marco Silva",
    homeStadium: "Craven Cottage",
    foundedYear: 1879,
    wins: 12,
    draws: 6,
    losses: 8,
    goalsScored: 48,
    goalsConceded: 41,
    players: [
      "Aleksandar Mitrović",
      "Andreas Pereira",
      "João Palhinha",
    ],
    country: "England",
  },
  {
    name: "Leeds United",
    coachName: "Jesse Marsch",
    homeStadium: "Elland Road",
    foundedYear: 1919,
    wins: 9,
    draws: 4,
    losses: 13,
    goalsScored: 38,
    goalsConceded: 48,
    players: [
      "Patrick Bamford",
      "Brenden Aaronson",
      "Rasmus Kristensen",
    ],
    country: "England",
  },
  {
    name: "Leicester City",
    coachName: "Brendan Rodgers",
    homeStadium: "King Power Stadium",
    foundedYear: 1884,
    wins: 11,
    draws: 7,
    losses: 10,
    goalsScored: 46,
    goalsConceded: 45,
    players: [
      "Jamie Vardy",
      "James Maddison",
      "Youri Tielemans",
    ],
    country: "England",
  },
  {
    name: "Liverpool",
    coachName: "Jürgen Klopp",
    homeStadium: "Anfield",
    foundedYear: 1892,
    wins: 17,
    draws: 6,
    losses: 5,
    goalsScored: 65,
    goalsConceded: 30,
    players: [
      "Mohamed Salah",
      "Sadio Mané",
      "Virgil van Dijk",
    ],
    country: "England",
  },
  {
    name: "Manchester City",
    coachName: "Pep Guardiola",
    homeStadium: "Etihad Stadium",
    foundedYear: 1880,
    wins: 20,
    draws: 4,
    losses: 2,
    goalsScored: 80,
    goalsConceded: 25,
    players: [
      "Erling Haaland",
      "Kevin De Bruyne",
      "Jack Grealish",
    ],
    country: "England",
  },
  {
    name: "Manchester United",
    coachName: "Erik ten Hag",
    homeStadium: "Old Trafford",
    foundedYear: 1878,
    wins: 15,
    draws: 5,
    losses: 6,
    goalsScored: 60,
    goalsConceded: 35,
    players: [
      "Bruno Fernandes",
      "Cristiano Ronaldo",
      "Marcus Rashford",
    ],
    country: "England",
  },
  {
    name: "Newcastle United",
    coachName: "Eddie Howe",
    homeStadium: "St James' Park",
    foundedYear: 1892,
    wins: 14,
    draws: 7,
    losses: 5,
    goalsScored: 55,
    goalsConceded: 32,
    players: [
      "Callum Wilson",
      "Miguel Almirón",
      "Bruno Guimarães",
    ],
    country: "England",
  },
  {
    name: "Nottingham Forest",
    coachName: "Steve Cooper",
    homeStadium: "City Ground",
    foundedYear: 1865,
    wins: 10,
    draws: 8,
    losses: 10,
    goalsScored: 40,
    goalsConceded: 45,
    players: [
      "Taiwo Awoniyi",
      "Morgan Gibbs-White",
      "Jesse Lingard",
    ],
    country: "England",
  },
  {
    name: "Southampton",
    coachName: "Ralph Hasenhüttl",
    homeStadium: "St Mary's Stadium",
    foundedYear: 1885,
    wins: 6,
    draws: 5,
    losses: 15,
    goalsScored: 35,
    goalsConceded: 50,
    players: [
      "James Ward-Prowse",
      "Che Adams",
      "Sékou Mara",
    ],
    country: "England",
  },
  {
    name: "Tottenham Hotspur",
    coachName: "Antonio Conte",
    homeStadium: "Tottenham Hotspur Stadium",
    foundedYear: 1882,
    wins: 16,
    draws: 5,
    losses: 7,
    goalsScored: 60,
    goalsConceded: 40,
    players: [
      "Harry Kane",
      "Son Heung-min",
      "Dejan Kulusevski",
    ],
    country: "England",
  },
  {
    name: "West Ham United",
    coachName: "David Moyes",
    homeStadium: "London Stadium",
    foundedYear: 1895,
    wins: 8,
    draws: 6,
    losses: 12,
    goalsScored: 35,
    goalsConceded: 45,
    players: [
      "Michail Antonio",
      "Jarrod Bowen",
      "Declan Rice",
    ],
    country: "England",
  },
  {
    name: "Wolverhampton Wanderers",
    coachName: "Bruno Lage",
    homeStadium: "Molineux Stadium",
    foundedYear: 1877,
    wins: 10,
    draws: 5,
    losses: 13,
    goalsScored: 40,
    goalsConceded: 40,
    players: [
      "Raúl Jiménez",
      "Adama Traoré",
      "Pedro Neto",
    ],
    country: "England",
  },
];


export const calculatePositions = (teamData: Team[]): RankedTeam[] => {
  return teamData
    .map(team => ({
      ...team,
      points: team.wins * 3 + team.draws,
      gamesPlayed: team.wins + team.draws + team.losses,
    }))
    .sort((a, b) => {
      if (b.points !== a.points) return b.points - a.points;
      if (b.goalsScored !== a.goalsScored) return b.goalsScored - a.goalsScored;
      return a.goalsConceded - b.goalsConceded;
    })
    .map((team, index) => ({
      ...team,
      position: index + 1,
    }));
};

export const getTeams = () => calculatePositions(teams);

export const addTeam = (team: Team) => {
  if (!teams.some(t => t.name === team.name)) {
    teams.push(team);
  }
  return calculatePositions(teams);
}

export const updateTeams = (newTeams: RankedTeam[]) => {
  teams.length = 0; 
  teams.push(...newTeams); 

  return getTeams(); 
};

export const deleteTeam = (teamName: string) => {
  // Find the index of the team to delete
  const teamIndex = teams.findIndex(team => team.name === teamName);
  
  // If team not found, return false
  if (teamIndex === -1) {
    return false;
  }
  
  // Remove the team from the array (mutate in-place)
  teams.splice(teamIndex, 1); // This directly modifies the original `teams` array
  
  // Recalculate positions for the remaining teams
  const rankedTeams = calculatePositions(teams);
  
  // Update the teams array (no need to spread or reassign, just mutate directly)
  updateTeams(rankedTeams);
  
  return true;
};
