plugins {
    java
    application
}

group = "socialapp"
version = "1.0"

repositories {
    mavenCentral()
}

dependencies {
    implementation("org.postgresql:postgresql:42.7.7")
}

java {
    sourceCompatibility = JavaVersion.VERSION_1_8
    targetCompatibility = JavaVersion.VERSION_1_8
}

tasks.withType<JavaCompile>().configureEach {
    options.encoding = "UTF-8"
    options.release.set(8)
}

application {
    mainClass.set("Main")
}


tasks.named<JavaExec>("run") {
    standardInput = System.`in`
}