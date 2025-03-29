"use client";

import React from "react";
import { useRouter } from "next/navigation";
import { Bar } from "react-chartjs-2";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { useTeams } from "../TeamContext";

ChartJS.register(CategoryScale, LinearScale, BarElement, Title, Tooltip, Legend);

const getChartData = (teams: any[]) => {
  const totalWins = teams.reduce((sum, team) => sum + team.wins, 0);
  const totalDraws = teams.reduce((sum, team) => sum + team.draws, 0);
  const totalLosses = teams.reduce((sum, team) => sum + team.losses, 0);
  const totalGoalsScored = teams.reduce((sum, team) => sum + team.goalsScored, 0);
  const totalGoalsConceded = teams.reduce((sum, team) => sum + team.goalsConceded, 0);

  return {
    labels: ["Wins", "Draws", "Losses", "Goals Scored", "Goals Conceded"],
    datasets: [
      {
        label: "Total Statistics",
        data: [totalWins, totalDraws, totalLosses, totalGoalsScored, totalGoalsConceded],
        backgroundColor: [
          "rgba(75, 192, 192, 0.6)", // Wins
          "rgba(54, 162, 235, 0.6)", // Draws
          "rgba(255, 99, 132, 0.6)", // Losses
          "rgba(153, 102, 255, 0.6)", // Goals Scored
          "rgba(255, 159, 64, 0.6)", // Goals Conceded
        ],
        borderColor: [
          "rgba(75, 192, 192, 1)",
          "rgba(54, 162, 235, 1)",
          "rgba(255, 99, 132, 1)",
          "rgba(153, 102, 255, 1)",
          "rgba(255, 159, 64, 1)",
        ],
        borderWidth: 1,
      },
    ],
  };
};

const getStatisticsReport = (teams: any[]) => {
  const totalTeams = teams.length;
  const totalPoints = teams.reduce((sum, team) => sum + (team.wins * 3 + team.draws), 0);
  const totalGoalsScored = teams.reduce((sum, team) => sum + team.goalsScored, 0);
  const totalGoalsConceded = teams.reduce((sum, team) => sum + team.goalsConceded, 0);

  const averagePoints = (totalPoints / totalTeams).toFixed(2);
  const averageGoalsScored = (totalGoalsScored / totalTeams).toFixed(2);
  const averageGoalsConceded = (totalGoalsConceded / totalTeams).toFixed(2);

  const highestPoints = Math.max(...teams.map((team) => team.wins * 3 + team.draws));
  const lowestPoints = Math.min(...teams.map((team) => team.wins * 3 + team.draws));

  return {
    totalTeams,
    averagePoints,
    averageGoalsScored,
    averageGoalsConceded,
    highestPoints,
    lowestPoints,
  };
};

export default function Statistics() {
  const router = useRouter();
  const { teams } = useTeams();
  const chartData = getChartData(teams);
  const statsReport = getStatisticsReport(teams);

  return (
    <div className="bg-black text-white min-h-screen p-6">
      <div className="container mx-auto bg-[#1d1d1d] text-gray-200 p-6 rounded-lg shadow-lg">
        <h2 className="text-2xl font-bold mb-4">League Statistics</h2>

        {/* Statistics Report */}
        <div className="mb-6 p-4 bg-gray-800 rounded-lg shadow-md">
          <h3 className="text-xl font-semibold mb-2">Statistics Report</h3>
          <p>Total Teams: <span className="font-bold">{statsReport.totalTeams}</span></p>
          <p>Average Points: <span className="font-bold">{statsReport.averagePoints}</span></p>
          <p>Average Goals Scored: <span className="font-bold">{statsReport.averageGoalsScored}</span></p>
          <p>Average Goals Conceded: <span className="font-bold">{statsReport.averageGoalsConceded}</span></p>
          <p>Highest Points: <span className="font-bold">{statsReport.highestPoints}</span></p>
          <p>Lowest Points: <span className="font-bold">{statsReport.lowestPoints}</span></p>
        </div>

        {/* Chart */}
        <Bar
          data={chartData}
          options={{
            responsive: true,
            plugins: {
              legend: {
                position: "top",
              },
              title: {
                display: true,
                text: "League Statistics",
              },
            },
          }}
        />

        {/* Back Button */}
        <button
          onClick={() => router.push("/")} // Navigate back to the main page
          className="mt-6 bg-blue-500 text-white px-4 py-2 rounded cursor-pointer"
        >
          Back to Home
        </button>
      </div>
    </div>
  );
}