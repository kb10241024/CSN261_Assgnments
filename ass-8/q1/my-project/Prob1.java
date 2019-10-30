/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.example.dijkstraimplementation;

import java.io.File;
import java.io.StringWriter;
import java.io.Writer;
import java.util.Map;
import org.jgrapht.Graph;
import org.jgrapht.graph.DefaultEdge;
import org.jgrapht.graph.DefaultWeightedEdge;
import org.jgrapht.graph.SimpleWeightedGraph;
import org.jgrapht.io.Attribute;
import org.jgrapht.io.EdgeProvider;
import org.jgrapht.io.GmlExporter;
import org.jgrapht.io.GmlImporter;
import org.jgrapht.io.VertexProvider;

/**
 * @author Kavya Barnwal
 */
public class Prob1 {

    private static String filePath = "L8_P1_sample.gml";

    public static void main(String[] args) throws Exception {
        Graph<Integer, DefaultWeightedEdge> g = new SimpleWeightedGraph<>(DefaultWeightedEdge.class);
        VertexProvider<Integer> vp = new VertexProvider<Integer>() {
            @Override
            public Integer buildVertex(String string, Map<String, Attribute> map) {
                return Integer.parseInt(string);
            }
        };
        EdgeProvider<Integer, DefaultWeightedEdge> ep = new EdgeProvider<Integer, DefaultWeightedEdge>() {
            @Override
            public DefaultWeightedEdge buildEdge(Integer v, Integer v1, String string, Map<String, Attribute> map) {
                return new DefaultWeightedEdge();
            }
        };
        GmlImporter<Integer, DefaultWeightedEdge> gmlImporter = new GmlImporter<>(vp, ep);
        gmlImporter.importGraph(g, new File(filePath));
        GmlExporter<Integer, DefaultWeightedEdge> exporter = new GmlExporter<>();
        Writer writer = new StDijkstraImplementationringWriter();
        exporter.exportGraph(g, writer);
        String graph1AsGraphML = writer.toString();

        // display
        System.out.println(graph1AsGraphML);
    }
}
