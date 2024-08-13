pipeline {
    agent any

    stages {
        stage('Cleanup') {
            steps {
                // Remove any existing JenkinsDemo directory
                sh 'rm -rf JenkinsDemo'
            }
        }

        stage('Checkout') {
            steps {
                // Clone the repository
                git url: 'https://github.com/bhoomikashirol/JenkinsDemo.git'
            }
        }

        stage('Build') {
            steps {
                script {
                    // Change to the Build directory and run CMake
                    dir('Build') {
                        sh 'cmake ../Code'
                        sh 'cmake --build .'
                    }
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    // Change to the Test directory and run the tests
                    dir('Test') {
                        sh 'g++ -o TestCode TestCode.cpp -lgtest -lgtest_main -pthread'
                        sh './TestCode'
                    }
                }
            }
        }

        stage('Archive') {
            steps {
                script {
                    // Archive the build files
                    dir('Build') {
                        archiveArtifacts artifacts: '**/*', allowEmptyArchive: true
                    }
                }
            }
        }
    }

    post {
        always {
            // Clean up workspace
            cleanWs()
        }
    }
}
