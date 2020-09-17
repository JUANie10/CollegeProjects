# Programs runs 9/17/2020. If the front-end of instagram changes, this script might not work.

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from time import sleep

#install chrome driver and move the .exe file to PATH location below
PATH = 'C:\Program Files (x86)\Google\Chrome\chromedriver.exe'
#----------------------------------------------------------------------------------------------------------------------
# Please type your username/phone number/email and your password within the quotation marks.
username = input("What is your username/phone number/email?\n")
password = input("What is your password?\n")
# Run the script :) enjoy
#----------------------------------------------------------------------------------------------------------------------

class InstaAnalyzer:
    # Storing the chrome webdriver, username and password within self
    def __init__(self, username, password):
        self.driver = webdriver.Chrome(PATH)
        self.wait = WebDriverWait(self.driver, 10)
        self.username = username
        self.password = password

    # Automates the Instagram login process
    def auto_login(self):
        # Loading Instagram on a Chrome Webdriver
        self.driver.get("https://www.instagram.com")

        # Waits for the page to load and locates username and password fields and inputs username and password
        username_input = self.wait.until(EC.presence_of_element_located(
            (By.XPATH, '//*[@id="loginForm"]/div/div[1]/div/label/input')))
        username_input.send_keys(self.username)

        password_input = self.driver.find_element_by_xpath('//*[@id="loginForm"]/div/div[2]/div/label/input')
        password_input.send_keys(self.password)

        # Clicking the login button
        login_button = self.driver.find_element_by_xpath('//*[@id="loginForm"]/div/div[3]/button').click()

        # Not saving login Credentials
        dont_save_login = self.wait.until(EC.presence_of_element_located(
            (By.XPATH, '/html/body/div[1]/section/main/div/div/div/div/button'))).click()

        # Not allowing notifications
        no_notifications = self.wait.until(EC.presence_of_element_located(
            (By.XPATH, '/html/body/div[4]/div/div/div/div[3]/button[2]'))).click()

    # Prints out a list of people you follow that don't follow you back
    def get_nonfollowers(self):

        # Navigating to profile
        go_to_profile = self.wait.until(EC.presence_of_element_located(
            (By.XPATH, '//*[@id="react-root"]/section/nav/div[2]/div/div/div[3]/div/div[5]/span/img'))).click()

        profile_button = self.wait.until(EC.presence_of_element_located(
            (By.XPATH, '//*[@id="react-root"]/section/nav/div[2]/div/div/div[3]/div/div[5]/div[2]/div/div[2]/div[2]/a[1]/div'))).click()

        # Getting the list of usernames from following
        following_button = self.wait.until(EC.presence_of_element_located(
            (By.XPATH, '//*[@id="react-root"]/section/main/div/header/section/ul/li[3]/a'))).click()

        following = self.get_usernames()

        # Getting the list of usernames from followers
        followers_button = self.driver.find_element_by_xpath('//*[@id="react-root"]/section/main/div/header/section/ul/li[2]/a').click()

        followers = self.get_usernames()

        # Getting the list of nonfollowers that you follow and printing their usernames
        non_followers = [username for username in following if username not in followers]
        print(non_followers)
        print(len(non_followers), "people do not following you back on instagram :(" )

    # Navigating through the follower and following boxes and returning a list full of usernames
    def get_usernames(self):

        username_box = self.wait.until(EC.presence_of_element_located((By.XPATH, "/html/body/div[4]/div/div/div[2]")))

        # initialize scroll height
        last_height = 0

        while True:

            # Waiting for usernames to load
            sleep(1)

            # Calculate new scroll height and compare with last scroll height
            new_height = self.driver.execute_script("""arguments[0].scrollTo(0, arguments[0].scrollHeight); 
                return arguments[0].scrollHeight;""", username_box)

            if new_height == last_height:
                break
            last_height = new_height
        # Getting the list of uernames
        list_username = username_box.find_elements_by_tag_name('a')

        usernames = [username.text for username in list_username if username.text != '']
        sleep(2)

        # Clicking the exit button
        exit_box = self.driver.find_element_by_xpath('/html/body/div[4]/div/div/div[1]/div/div[2]/button').click()

        return usernames

    # Runs the unfollowers script and terminates the webdriver
    def instaUnfollowers(self):
        self.auto_login()
        self.get_nonfollowers()
        self.driver.close()



# Main
profile = InstaAnalyzer(username, password)
profile.instaUnfollowers()

