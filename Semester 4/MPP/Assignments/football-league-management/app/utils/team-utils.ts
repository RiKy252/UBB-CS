import { TeamType } from "../types/team"; 

export function processTeamsForDisplay(teams: TeamType[]): TeamType[] {
  // Sort teams by points (descending) to determine positions
  const sortedTeams = [...teams].sort((a, b) => {
    // Calculate points for each team (3 for win, 1 for draw)
    const pointsA = (a.wins * 3) + a.draws;
    const pointsB = (b.wins * 3) + b.draws;
    
    // Sort by points (descending)
    if (pointsB !== pointsA) {
      return pointsB - pointsA;
    }
    
    // If points are equal, sort by goal difference
    const goalDiffA = a.goalsScored - a.goalsConceded;
    const goalDiffB = b.goalsScored - b.goalsConceded;
    
    if (goalDiffB !== goalDiffA) {
      return goalDiffB - goalDiffA;
    }
    
    // If goal difference is equal, sort by goals scored
    if (b.goalsScored !== a.goalsScored) {
      return b.goalsScored - a.goalsScored;
    }
    
    // If still tied, sort alphabetically
    return a.name.localeCompare(b.name);
  });

  // Calculate average wins
  const totalWins = sortedTeams.reduce((sum, team) => sum + team.wins, 0);
  const averageWins = totalWins / sortedTeams.length;

  // Find team with most and least wins
  let maxWins = -1;
  let minWins = Number.MAX_SAFE_INTEGER;
  
  sortedTeams.forEach(team => {
    if (team.wins > maxWins) maxWins = team.wins;
    if (team.wins < minWins) minWins = team.wins;
  });

  // Enhance each team with additional calculated properties
  return sortedTeams.map((team, index) => {
    // Calculate games played and points
    const gamesPlayed = team.wins + team.draws + team.losses;
    const points = (team.wins * 3) + team.draws;
    
    // Determine metadata for highlighting teams
    const metadata = {
      isMostWins: team.wins === maxWins,
      isLeastWins: team.wins === minWins,
      isAvgWins: Math.abs(team.wins - averageWins) < 1 // Within 1 win of average
    };
    
    return {
      ...team,
      position: index + 1, // Add position based on sorted index
      gamesPlayed,
      points,
      metadata
    };
  });
}

export function filterAndSortTeams(
  teams: TeamType[], 
  query?: string, 
  sortBy: keyof TeamType = 'points', 
  order: 'asc' | 'desc' = 'desc'
): TeamType[] {
  // First process teams to ensure they have all required properties
  const processedTeams = processTeamsForDisplay(teams);
  
  // Filter by search query if provided
  const filteredTeams = query 
    ? processedTeams.filter(team => 
        team.name.toLowerCase().includes(query.toLowerCase()) ||
        team.coachName.toLowerCase().includes(query.toLowerCase()) ||
        team.homeStadium.toLowerCase().includes(query.toLowerCase()) ||
        team.country.toLowerCase().includes(query.toLowerCase())
      )
    : processedTeams;
  
  // Sort by the specified criteria and order
  return filteredTeams.sort((a, b) => {
    let valueA = a[sortBy];
    let valueB = b[sortBy];
    
    // Handle string comparisons
    if (typeof valueA === 'string' && typeof valueB === 'string') {
      return order === 'asc' 
        ? valueA.localeCompare(valueB) 
        : valueB.localeCompare(valueA);
    }
    
    // Handle number comparisons (including undefined values)
    valueA = valueA === undefined ? 0 : valueA;
    valueB = valueB === undefined ? 0 : valueB;
    
    return order === 'asc' 
      ? Number(valueA) - Number(valueB) 
      : Number(valueB) - Number(valueA);
  });
}