// models/index.js
import sequelize from '../config/database';
import Team from './Team';

// Initialize models
const models = {
  Team
};

// Create associations if needed
// Example: Team.hasMany(Player);

// Sync all models with database
const syncDatabase = async () => {
  try {
    await sequelize.sync({ alter: true }); // Use { force: true } to drop and recreate tables (careful in production!)
    console.log('All models were synchronized successfully.');
  } catch (error) {
    console.error('Error synchronizing models:', error);
  }
};

syncDatabase();

export { Team };
export default models;