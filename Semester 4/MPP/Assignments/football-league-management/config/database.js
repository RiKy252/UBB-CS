// config/database.js
import { Sequelize } from 'sequelize';
import dotenv from 'dotenv';

dotenv.config();

// Use environment variables for database connection
const sequelize = new Sequelize(
  process.env.DB_NAME || 'football_league',
  process.env.DB_USER || 'postgres',
  process.env.DB_PASSWORD || 'Riki01$$',
  {
    host: process.env.DB_HOST || 'localhost',
    dialect: 'postgres',
    dialectModule: 'postgres',
    logging: false, // Set to console.log to see SQL queries
    pool: {
      max: 5,
      min: 0,
      acquire: 30000,
      idle: 10000
    }
  }
);

// Test the connection
const testConnection = async () => {
  try {
    await sequelize.authenticate();
    console.log('Database connection established successfully.');
  } catch (error) {
    console.error('Unable to connect to the database:', error);
  }
};

testConnection();

export default sequelize;