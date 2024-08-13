pipeline {
    agent any

    stages {
        stage('Preparation') {
            steps {
                // Clean up workspace
                cleanWs()
                
                // Clone the public repository
                git branch: 'main', url: 'https://github.com/bhoomika-shirol/JenkinsDemo.git'
            }
        }
        
        stage('Build') {
            steps {
                sh '''
                    mkdir -p build
                    cd build
                    cmake ..
                    make
                '''
            }
        }
        
        stage('Test') {
            steps {
                sh '''
                    cd build
                    ./unit_test
                '''
            }
        }
    }
    
    post {
        always {
            // Clean up workspace at the end
            cleanWs()
        }
    }
}
