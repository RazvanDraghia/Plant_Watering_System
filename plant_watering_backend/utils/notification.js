const admin = require('firebase-admin');

exports.sendNotification = (message) => {
  const payload = {
    notification: {
      title: 'Plant Watering Alert',
      body: message
    }
  };

  // Send notification to a topic or specific device token
  admin.messaging().sendToTopic('plantAlerts', payload)
    .then((response) => console.log('Notification sent successfully:', response))
    .catch((error) => console.error('Error sending notification:', error));
};
