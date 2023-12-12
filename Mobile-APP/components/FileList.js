import React from "react";
import { View, Text, StyleSheet } from "react-native";

const FileList = ({ files }) => {
  return (
    <View style={styles.container}>
      <Text style={styles.title}>
        {files.length > 0 ? "Available Files" : "No Files Available"}
      </Text>
      {files.map((file, index) => (
        <Text key={index} style={styles.text}>
          {file}
        </Text>
      ))}
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    backgroundColor: "#fff",
    padding: 10,
    borderRadius: 10,
    marginBottom: 20,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.2,
    shadowRadius: 2,
    elevation: 2,
  },
  title: {
    fontSize: 18,
    fontWeight: "bold",
    marginBottom: 10,
    color: "#333",
  },
  text: {
    fontSize: 16,
    color: "#666",
    marginBottom: 5,
  },
});

export default FileList;
