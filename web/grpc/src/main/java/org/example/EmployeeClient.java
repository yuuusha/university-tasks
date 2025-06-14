package org.example;

import com.example.grpc.EmployeeRequest;
import com.example.grpc.EmployeeResponse;
import com.example.grpc.EmployeeServiceGrpc;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;

public class EmployeeClient {
    public static void main(String[] args) {
        ManagedChannel channel = ManagedChannelBuilder.forAddress("localhost", 9090)
                .usePlaintext()
                .build();

        EmployeeServiceGrpc.EmployeeServiceBlockingStub stub = EmployeeServiceGrpc.newBlockingStub(channel);

        EmployeeRequest request = EmployeeRequest.newBuilder()
                .setLastName("Popov")
                .setFirstName("Sergey")
                .setMiddleName("Andreevich")
                .setGender("male")
                .setBirthDate("1990-05-20")
                .setPhone("+7(495)123-4567")
                .setHireDate("2024-02-20")
                .setFireDate("")
                .setPosition("Software Engineer")
                .setSalary(120000)
                .setIsManager(false)
                .setDepartmentId(2)
                .build();

        EmployeeResponse response = stub.addEmployee(request);
        if (response.getEmployeeId() != -1) {
            System.out.println("Employee added with ID: " + response.getEmployeeId());
        } else {
            System.out.println("Error: " + response.getErrorMessage());
        }

        channel.shutdown();
    }
}

