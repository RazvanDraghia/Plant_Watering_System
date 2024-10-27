const express = require('express');
const bodyParser = require('body-parser');
const admin = require('firebase-admin');
const dotenv = require('dotenv');
const cors = require('cors');

dotenv.config();

const app = express();
app.use(bodyParser.json());
app.use(cors());

// Initialize Firebase Admin SDK
const serviceAccount = require(process.env.FIREBASE_SERVICE_ACCOUNT_PATH);
admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
});

// Firestore database reference
const db = admin.firestore();

// Example route to get plant data
app.get('/plants', async (req, res) => {
  try {
    const snapshot = await db.collection('plants').get();
    const plants = snapshot.docs.map(doc => ({ id: doc.id, ...doc.data() }));
    res.status(200).json(plants);
  } catch (error) {
    console.error("Error fetching plants:", error);
    res.status(500).send("Error fetching plants");
  }
});

// Example route to add a new plant
app.post('/plants', async (req, res) => {
  try {
    const newPlant = req.body;
    const plantRef = await db.collection('plants').add(newPlant);
    res.status(201).json({ id: plantRef.id, ...newPlant });
  } catch (error) {
    console.error("Error adding plant:", error);
    res.status(500).send("Error adding plant");
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
