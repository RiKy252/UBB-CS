// TODO, caz eronat la search de ex, sa dau eroare 404 daca foloseste un query in urma 
// caruia sa nu se gaseasca echipa (si schimbat si in test)

import { NextResponse } from "next/server";
import { getTeams } from "../data";

export async function GET(req: Request) {
  const { searchParams } = new URL(req.url);

  const query = searchParams.get("query")?.toLowerCase() || "";
  const sortBy = searchParams.get("sortBy") || "points";
  const order = searchParams.get("order") || "desc";

  let teams = getTeams(); 

  const winsArray = [...teams].map((t) => t.wins);
  const maxWins = Math.max(...winsArray);
  const minWins = Math.min(...winsArray);
  const avgWins = winsArray.reduce((acc, val) => acc + val, 0) / winsArray.length;

  // Filter teams by query (if any)
  if (query) {
    teams = teams.filter((team) =>
      team.name.toLowerCase().includes(query)
    );
  }

  if (!teams) {
    
  }

  const sortedTeams = [...teams].sort((a, b) => {
    let valA, valB;

    switch (sortBy) {
      case "points":
        valA = a.points;
        valB = b.points;
        break;
      case "wins":
        valA = a.wins;
        valB = b.wins;
        break;
      case "goalsScored":
        valA = a.goalsScored;
        valB = b.goalsScored;
        break;
      case "goalsConceded":
        valA = a.goalsConceded;
        valB = b.goalsConceded;
        break;
      case "name":
      default:
        valA = a.name.toLowerCase();
        valB = b.name.toLowerCase();
    }

    if (valA < valB) return order === "asc" ? -1 : 1;
    if (valA > valB) return order === "asc" ? 1 : -1;
    return 0;
  });

  const enhancedTeams = sortedTeams.map((team) => ({
    ...team,
    metadata: {
      isMostWins: team.wins === maxWins,
      isLeastWins: team.wins === minWins,
      isAvgWins: Math.abs(team.wins - avgWins) < 1,
    },
  }));

  return NextResponse.json(enhancedTeams);
}
