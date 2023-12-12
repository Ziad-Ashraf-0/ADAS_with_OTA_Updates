import {
  View,
  Image,
  SafeAreaView,
  Text,
  StyleSheet,
  TextInput,
  Pressable,
} from "react-native";
import React, { useState } from "react";
import { Stack, useRouter } from "expo-router";
import Logo from "../assets/car.png";
import Container from "../components/Container";

const Home = () => {
  const router = useRouter();
  const [inputText, setInputText] = useState("");

  const handleInputChange = (text) => {
    setInputText(text);
  };

  return (
    <Container>
      <SafeAreaView>
        <Stack.Screen
          options={{
            headerTransparent: true,
            headerShadowVisible: false,
            headerTitle: "",
          }}
        />

        <View style={styles.container}>
          <Text className="text-white text-4xl">FOTA APP</Text>
          <Image className="mt-20" source={Logo} />
          <Text className="text-white mt-8">Enter IP Address Of ESP32</Text>
          <TextInput
            style={styles.input}
            value={inputText}
            onChangeText={handleInputChange}
            placeholder="Enter IP address....."
            placeholderTextColor="gray"
            color="white"
          />
          <Pressable
            className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-4 px-16 rounded mt-10"
            onPress={() => {
              if (inputText) {
                router.push({
                  pathname: "/Dashboard",
                  params: { ip: inputText },
                });
              } else {
                alert("pls enter IP address...");
              }
            }}
          >
            <Text style={styles.text}>Continue</Text>
          </Pressable>
        </View>
      </SafeAreaView>
    </Container>
  );
};

const styles = StyleSheet.create({
  container: {
    justifyContent: "center",
    alignItems: "center",
  },
  input: {
    width: "80%",
    height: 40,
    borderColor: "gray",
    borderWidth: 1,
    marginBottom: 10,
    marginTop: 10,
    paddingHorizontal: 10,
  },
  button: {
    marginTop: 50,
    alignItems: "center",
    justifyContent: "center",
    paddingVertical: 12,
    paddingHorizontal: 32,
    borderRadius: 4,
    elevation: 3,
  },
  text: {
    fontSize: 16,
    lineHeight: 21,
    fontWeight: "bold",
    letterSpacing: 0.25,
    color: "white",
  },
});

export default Home;
