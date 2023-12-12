import axios from "axios";
import { Stack, useSearchParams } from "expo-router";
import React, { useEffect, useState } from "react";
import {
  TouchableOpacity,
  SafeAreaView,
  StyleSheet,
  Text,
  Image,
  View,
} from "react-native";

import Home from "../assets/home.png";
import Menu from "../assets/menu.png";
import Profile from "../assets/profile.png";
import {
  DownloadLatestVER,
  FileList,
  LoadingIndicator,
  OptionMenu,
  ScreenHeaderBtn,
  SendFile,
} from "../components";

// Import arrow icons or use your own images

import rightArrow from "../assets/right-arrow.png";
import leftArrow from "../assets/left-arrow.png";
import upArrow from "../assets/up-arrow.png";
import downArrow from "../assets/down-arrow.png";
import Stop from "../assets/stop-button.png";

const dashboard = () => {
  const [isLoading, setIsLoading] = useState(true);
  const [fetching, setIsFetching] = useState(false);
  const [selectedOption, setSelectedOption] = useState("default");
  const [data, setData] = useState("");
  const [files, setFiles] = useState([]);
  const { ip } = useSearchParams();

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.post(`http://${ip}/data`, {
          data: "get-info",
        });
        console.log(response.data); // Do something with the response
        setData(response.data.response);
        setIsLoading(false);
      } catch (error) {
        console.error(error);
      }
    };

    if (ip) {
      console.log(ip);
      fetchData();
    }
  }, []);

  const handleDirButtonPress = (direction, rightSpeed, leftSpeed) => {
    // Define your API endpoint
    const apiUrl = `http://${ip}/move`;

    // Create the request body
    const requestBody = {
      direction,
      rightSpeed,
      leftSpeed,
    };

    // Make the Axios POST request
    axios
      .post(apiUrl, requestBody)
      .then((response) => {
        // Handle success, if needed
        console.log("Request successful", response.data);
      })
      .catch((error) => {
        // Handle error, if needed
        console.error("Error making request", error);
      });
  };

  const handleButtonPress = (buttonId) => {
    switch (buttonId) {
      case "1":
        axios
          .post(`http://${ip}/data`, { data: "list-files" })
          .then((response) => {
            setFiles(response.data.files);
            setSelectedOption("list-files");
          })
          .catch((error) => console.error(error));
        break;
      case "2":
        axios
          .post(`http://${ip}/data`, { data: "delete-files" })
          .then((response) => {
            console.log(response.data);
            setSelectedOption("delete-files");
            alert("Files Deleted");
          })
          .catch((error) => console.error(error));
        break;
      case "3":
        setIsFetching(true);
        setSelectedOption("download-file");
        axios
          .post(
            `http://${ip}/data`,
            { data: "download-file" },
            { timeout: 8000 }
          )
          .then((response) => {
            console.log(response.data);
            setIsFetching(false);
          })
          .catch((error) => console.error(error));
        break;
      case "4":
        setIsFetching(true);
        setSelectedOption("send-binary");
        axios
          .post(
            `http://${ip}/data`,
            { data: "send-binary" },
            { timeout: 30000 }
          )
          .then((response) => {
            setIsFetching(false);
            console.log(response.data);
          })
          .catch((error) => console.error(error));
        break;
        case "5":
          setIsFetching(true);
          setSelectedOption("autopark");
          axios
            .post(
              `http://${ip}/control`,
              { mode: 0x99 },
              { timeout: 8000 }
            )
            .then((response) => {
              setIsFetching(false);
              console.log(response.data);
            })
            .catch((error) => console.error(error));
          break;
          case "6":
            setIsFetching(true);
            setSelectedOption("adaptive");
            axios
              .post(
                `http://${ip}/control`,
                { mode: 0xA7 },
                { timeout: 8000 }
              )
              .then((response) => {
                setIsFetching(false);
                console.log(response.data);
              })
              .catch((error) => console.error(error));
            break;
      default:
        console.log(`Unknown button ID: ${buttonId}`);
    }
  };

  return (
    <>
      {isLoading ? (
        <>
          <Stack.Screen
            options={{
              headerTransparent: true,
              headerShadowVisible: false,
              headerTitle: "",
            }}
          />
          <LoadingIndicator />
        </>
      ) : (
        <SafeAreaView style={styles.container}>
          <Stack.Screen
            component={null}
            options={{
              headerShadowVisible: false,
              headerTitle: "",
              headerStyle: {
                backgroundColor: "#202326",
              },
              headerLeft: () => (
                <View style={styles.headerButtonWrapper}>
                  <ScreenHeaderBtn iconUrl={Menu} dimension="80%" />
                </View>
              ),
              headerRight: () => (
                <View style={styles.headerButtonWrapper}>
                  <ScreenHeaderBtn iconUrl={Profile} dimension="100%" />
                </View>
              ),
            }}
          />
          <View style={styles.contentContainer}>
            <Text style={styles.text}>Avaliable Devices :</Text>
            <Text style={styles.text}>
              STM32F429I <Text style={styles.data}>VER {data}</Text>
            </Text>
            <OptionMenu onPressButton={handleButtonPress} />

            {/* Render a component based on the selected option */}
            {selectedOption && (
              <>
                {selectedOption === "list-files" && <FileList files={files} />}
                {selectedOption === "download-file" && (
                  <DownloadLatestVER fetching={fetching}></DownloadLatestVER>
                )}
                {selectedOption === "delete-file" && <></>}
                {selectedOption === "send-binary" && (
                  <SendFile fetching={fetching}></SendFile>
                )}
              </>
            )}

            <View style={styles.containerButtons}>
              {/* Keypad or joystick buttons */}
              <View style={styles.keypad}>
                {/* First Row: Up Arrow */}
                <View style={styles.directionButtonRow}>
                  <TouchableOpacity
                    style={[styles.directionButton]}
                    onPress={() => {
                      handleDirButtonPress(0x77, 100, 100);
                    }}
                  >
                    <Image source={upArrow} style={{ width: 40, height: 40 }} />
                  </TouchableOpacity>
                </View>

                {/* Second Row: Left and Right Arrows */}
                <View style={styles.directionButtonRow}>
                  <TouchableOpacity
                    style={[styles.directionButton, styles.leftArrowButton]}
                    onPress={() => {
                      handleDirButtonPress(0xAB, 50, 100);
                    }}
                  >
                    <Image
                      source={leftArrow}
                      style={{ width: 40, height: 40 }}
                    />
                  </TouchableOpacity>

                  <TouchableOpacity
                    style={[styles.directionButton]}
                    onPress={() => {
                      handleDirButtonPress(0xCC, 0, 0);
                    }}
                  >
                    <Image source={Stop} style={{ width: 40, height: 40 }} />
                  </TouchableOpacity>

                  <TouchableOpacity
                    style={[styles.directionButton, styles.rightArrowButton]}
                    onPress={() => {
                      handleDirButtonPress(0x80, 50, 100);
                    }}
                  >
                    <Image
                      source={rightArrow}
                      style={{ width: 40, height: 40 }}
                    />
                  </TouchableOpacity>
                </View>

                {/* Third Row: Down Arrow */}
                <View style={styles.directionButtonRow}>
                  <TouchableOpacity
                    style={[styles.directionButton]}
                    onPress={() => {
                      handleDirButtonPress(0x79, 50, 100);
                    }}
                  >
                    <Image
                      source={downArrow}
                      style={{ width: 40, height: 40 }}
                    />
                  </TouchableOpacity>
                </View>
              </View>
            </View>

            <View style={styles.footer}>
              <ScreenHeaderBtn iconUrl={Home} dimension="60%" />
              <ScreenHeaderBtn iconUrl={Menu} dimension="80%" />
              <ScreenHeaderBtn iconUrl={Menu} dimension="80%" />
              <ScreenHeaderBtn iconUrl={Menu} dimension="80%" />
            </View>
          </View>
        </SafeAreaView>
      )}
    </>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#202326",
  },
  containerButtons: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
  },
  contentContainer: {
    flex: 1,
    marginTop: 120,
    paddingHorizontal: 20,
    backgroundColor: "#202326",
  },
  data: {
    fontSize: 14,
    color: "#999999",
    fontStyle: "italic",
  },
  footer: {
    position: "absolute",
    bottom: 25,
    flexDirection: "row",
    justifyContent: "space-between",
    left: 40,
    right: 40,
  },
  leftArrowButton: {
    marginRight: 10, // Add margin to the right for the left arrow button
  },
  rightArrowButton: {
    marginLeft: 10, // Add margin to the left for the right arrow button
  },
  text: {
    fontSize: 18,
    fontWeight: "bold",
    color: "#fff",
  },
  headerButtonWrapper: {
    marginVertical: 15,
  },
  keypad: {
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
    marginTop: 20,
  },
  directionButtonRow: {
    flexDirection: "row",
    justifyContent: "center",
    alignItems: "center",
  },
  directionButton: {
    width: 60,
    height: 60,
    borderRadius: 10,
    backgroundColor: "#3498db",
    margin: 5,
    justifyContent: "center",
    alignItems: "center",
  },
  upArrow: {},
  leftArrow: {
    paddingRight: 10,
  },
  rightArrow: {
    transform: [{ rotate: "90deg" }], // rotate right 90 degrees
  },
  downArrow: {
    transform: [{ rotate: "180deg" }], // rotate down 180 degrees
  },
  buttonText: {
    color: "white",
    fontSize: 18,
  },
});

export default dashboard;
