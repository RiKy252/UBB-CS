"use client";

import React, { useState, useEffect } from "react";
import { useRouter } from "next/navigation";

import { ChartData, ChartOptions, CategoryScale, LinearScale, BarElement, Title, Tooltip, Legend, PointElement, LineElement, ArcElement } from 'chart.js';
import { Bar, Line, Pie } from "react-chartjs-2";
import { Chart as ChartJS } from "chart.js"

import { useTeams } from "../TeamContext";

ChartJS.register(
  CategoryScale,  // For category axis (Bar chart, etc.)
  LinearScale,    // For numeric axis (Line chart, etc.)
  BarElement,     // For Bar chart
  PointElement,   // For Line chart
  LineElement,    // For Line chart
  ArcElement,     // For Pie chart
  Title,          // For chart title
  Tooltip,        // For tooltips
  Legend          // For chart legend
);

// Define data types for charts
interface TeamData {
  name: string;
  wins: number;
  losses: number;
  goals: number;
}

interface BarChartData {
  labels: string[];
  datasets: {
    label: string;
    data: number[];
    backgroundColor: string;
  }[];
}

interface LineChartData {
  labels: string[];
  datasets: {
    label: string;
    data: number[];
    borderColor: string;
    fill: boolean;
  }[];
}

interface PieChartData {
  labels: string[];
  datasets: {
    data: number[];
    backgroundColor: string[];
  }[];
}

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

const generateRandomColors = (numColors: number) => {
  return Array.from({ length: numColors }, () =>
    `hsl(${Math.floor(Math.random() * 360)}, 70%, 50%)` // Generates random colors using HSL
  );
};


export default function Statistics() {
  const router = useRouter();
  const { teams, setTeams, addMoreFakeTeams } = useTeams();
  const chartData = getChartData(teams);
  const statsReport = getStatisticsReport(teams);

  const [barChartData, setBarChartData] = useState<BarChartData>({
    labels: [],
    datasets: [{ label: 'Wins vs Losses', data: [], backgroundColor: '' }]
  });

  const [lineChartData, setLineChartData] = useState<LineChartData>({
    labels: [],
    datasets: [{ label: 'Goals Scored Over Time', data: [], borderColor: 'blue', fill: false }]
  });

  const [pieChartData, setPieChartData] = useState<PieChartData>({
    labels: [],
    datasets: [{ data: [], backgroundColor: [] }]
  });

  useEffect(() => {
    // Simulating an API call to get team data
    const fetchTeamData = async () => {
      const response = await fetch('/api/teams'); // Replace with actual endpoint
      const data = await response.json();
      setTeams(data);
    };

    fetchTeamData();
  }, []);

  useEffect(() => {
    if (teams.length > 0) {
      const labels = teams.map(team => team.name);
      const winsData = teams.map(team => team.wins);
      const lossesData = teams.map(team => team.losses);
      const goalsData = teams.map(team => team.goalsScored);
      const backgroundColors = generateRandomColors(teams.length);

      setBarChartData({
        labels,
        datasets: [
          {
            label: 'Wins',
            data: winsData,
            backgroundColor: 'green',
          },
          {
            label: 'Losses',
            data: lossesData,
            backgroundColor: 'red',
          }
        ]
      });

      setLineChartData({
        labels,
        datasets: [
          {
            label: 'Goals Scored Over Time',
            data: goalsData,
            borderColor: 'blue',
            fill: false
          }
        ]
      });

      setPieChartData({
        labels,
        datasets: [
          {
            data: winsData,
            backgroundColor: backgroundColors,
          }
        ]
      });
    }
  }, [teams]);

  return (
    <div className="bg-black text-white min-h-screen p-6">
      <div className="container mx-auto bg-[#1d1d1d] text-gray-200 p-6 rounded-lg shadow-lg">
        <h2 className="text-2xl font-bold mb-4">League Statistics</h2>

        {/* Button to Add More Teams */}
        <button
          onClick={addMoreFakeTeams} // Trigger to add more teams
          className="mb-6 bg-blue-500 text-white px-4 py-2 rounded cursor-pointer"
        >
          Add More Teams
        </button>

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

        {/* Team statistics */}
        <h1 className="text-3xl font-bold mb-6 mt-6">Team Statistics</h1>

        <Bar data={barChartData} />
        <Line data={lineChartData} />
        <div className="w-full h-[95vh]">
          <Pie data={pieChartData} />
        </div>
        </div>    

          {/* Back Button */}
          <button
            onClick={() => router.push("/")} // Navigate back to the main page
            className="mt-6 bg-blue-500 text-white px-4 py-2 rounded cursor-pointer"
          >
            Back to Home
          </button>
    </div>
  );
}