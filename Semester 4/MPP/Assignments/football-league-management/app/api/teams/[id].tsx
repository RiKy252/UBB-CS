import { NextResponse } from "next/server";
import { Team, teams, updateTeams } from "./data";

export async function GET(req: Request, { params }: { params: { id: string } }) {
    const team = teams.find((t) => t.id === params.id);
    if (!team) {
      return NextResponse.json({ error: "Team not found" }, { status: 404 });
    }
    return NextResponse.json(team);
  }
  
  export async function DELETE(req: Request, { params }: { params: { id: string } }) {
    const newTeams = teams.filter((t) => t.id !== params.id);
  
    if (newTeams.length === teams.length) {
      return NextResponse.json({ error: "Team not found" }, { status: 404 });
    }
  
    updateTeams(newTeams); // Modify the in-memory array
    return NextResponse.json({ message: "Team deleted successfully" });
  }
  
  export async function PATCH(req: Request, { params }: { params: { id: string } }) {
    try {
      const teamIndex = teams.findIndex((t) => t.id === params.id);
      if (teamIndex === -1) {
        return NextResponse.json({ error: "Team not found" }, { status: 404 });
      }
  
      const updatedData = await req.json();
      teams[teamIndex] = { ...teams[teamIndex], ...updatedData };
  
      updateTeams([...teams]); // Save changes
      return NextResponse.json(teams[teamIndex]);
    } catch (error) {
      return NextResponse.json({ error: "Invalid data" }, { status: 400 });
    }
  }
