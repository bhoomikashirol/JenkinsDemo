pipeline {
    agent any

    environment {
        BUILD_DIR = "/var/lib/jenkins/workspace/PipelineDemo/build"
    }

    stages {
        stage('Checkout') {
            steps {
                script {
                    // Checkout the main branch
                    checkout([$class: 'GitSCM', branches: [[name: '*/main']], userRemoteConfigs: [[url: 'https://github.com/bhoomikashirol/JenkinsDemo.git']]])
                    
                    // Checkout the Code branch
                    dir('Code') {
                        checkout([$class: 'GitSCM', branches: [[name: '*/Code']], userRemoteConfigs: [[url: 'https://github.com/bhoomikashirol/JenkinsDemo.git']]])
                    }
                    
                    // Checkout the Test branch
                    dir('Test') {
                        checkout([$class: 'GitSCM', branches: [[name: '*/Test']], userRemoteConfigs: [[url: 'https://github.com/bhoomikashirol/JenkinsDemo.git']]])
                    }
                }
            }
        }

        stage('Build') {
            steps {
                script {
                    // Create the build directory
                    sh 'mkdir -p ${BUILD_DIR}'
                    
                    // Run CMake and build
                    sh 'cmake -S . -B ${BUILD_DIR}'
                    sh 'cmake --build ${BUILD_DIR}'
                }
            }
        }

        stage('Cppcheck') {
            steps {
                script {
                    // Run Cppcheck
                    sh 'cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck.xml'
                }
                // Publish Cppcheck results
                publishCppcheck pattern: 'cppcheck.xml'
            }
        }

        stage('Test') {
            steps {
                script {
                    // Run the unit tests
                    sh '${BUILD_DIR}/unit_test'
                }
            }
        }
    }
}
```

Let me know if you need any further modifications!
