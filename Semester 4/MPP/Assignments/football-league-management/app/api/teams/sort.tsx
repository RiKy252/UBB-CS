import { NextResponse } from "next/server";
import { teams } from "./data";

export async function GET(req: Request) {
  const { searchParams } = new URL(req.url);

  // Get sorting criteria
  const sortBy = searchParams.get("sortBy") || "points";
  const order = searchParams.get("order") || "desc"; 

  const teamsWithPoints = teams.map(team => ({
    ...team,
    points: team.wins * 3 + team.draws
  }));

  // Sorting function
  const sortedTeams = teamsWithPoints.sort((a, b) => {
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

  return NextResponse.json(sortedTeams);
}
