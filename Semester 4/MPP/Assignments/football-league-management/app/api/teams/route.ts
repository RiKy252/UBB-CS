import { NextResponse } from "next/server";
import { getTeams, addTeam, updateTeams } from "./data"

export async function GET() {
  const teams = getTeams(); // Fetch the teams from the data source
  const winsArray = [...teams].map((t) => t.wins);
  const maxWins = Math.max(...winsArray);
  const minWins = Math.min(...winsArray);
  const avgWins = winsArray.reduce((acc, val) => acc + val, 0) / winsArray.length;
  const enhancedTeams = [...teams].map((team) => ({
    ...team,
    metadata: {
      isMostWins: team.wins === maxWins,
      isLeastWins: team.wins === minWins,
      isAvgWins: Math.abs(team.wins - avgWins) < 1,
    },
  }));
  return NextResponse.json(enhancedTeams);
}

export async function POST(req: Request) {
  try {
    const { name, coachName, homeStadium, foundedYear, wins, draws, losses, goalsScored, goalsConceded, players, country } = await req.json();
    
    if (!name || !coachName) {
      return NextResponse.json({ error: "Name and coach name are required" }, { status: 400 });
    }

    const newTeams = addTeam({
      name,
      coachName,
      homeStadium,
      foundedYear,
      wins,
      draws,
      losses,
      goalsScored,
      goalsConceded,
      players,
      country,
    });

    return NextResponse.json(newTeams, { status: 201 });

  } catch (error) {
    return NextResponse.json({ error: "Invalid data" }, { status: 400 });
  }
}
