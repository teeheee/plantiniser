pipeline {
    agent none
    stages {
        stage('Building firmware') {
            agent {
                docker { 
                   image 'infinitecoding/platformio-for-ci' 
                   args '-u root:root'
                }
            }
            steps {
                sh 'pio run -e main'
            }
        }
        stage ('Deploy firmware') {
            steps{
                commitId = sh(returnStdout: true, script: 'git rev-list --count HEAD)')
                sshagent(credentials : ['use-the-id-from-credential-generated-by-jenkins'])
                {
                    sh 'scp ./.pio/build/main/firmware.bin alex@host:~/plantiniser_firmware_provider/opt/'+commitId+'.bin'
                }
            }
        }
        stage('Building image') {
            steps{
                script {
                    dockerImage = docker.build("local:plantiniser_firmware_provider","scripts")
                }
            }
        }
    }
}
