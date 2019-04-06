/*
 * Copyright 2017-present Open Networking Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.onosproject.p4tutorial.pipeconf;

import org.apache.felix.scr.annotations.Activate;
import org.apache.felix.scr.annotations.Component;
import org.apache.felix.scr.annotations.Deactivate;
import org.apache.felix.scr.annotations.Reference;
import org.apache.felix.scr.annotations.ReferenceCardinality;
import org.onosproject.driver.pipeline.DefaultSingleTablePipeline;
import org.onosproject.net.behaviour.Pipeliner;
import org.onosproject.net.device.PortStatisticsDiscovery;
import org.onosproject.net.pi.model.DefaultPiPipeconf;
import org.onosproject.net.pi.model.PiPipeconf;
import org.onosproject.net.pi.model.PiPipeconfId;
import org.onosproject.net.pi.model.PiPipelineInterpreter;
import org.onosproject.net.pi.model.PiPipelineModel;
import org.onosproject.net.pi.service.PiPipeconfService;
import org.onosproject.p4runtime.model.P4InfoParser;
import org.onosproject.p4runtime.model.P4InfoParserException;

import java.net.URL;

import static org.onosproject.net.pi.model.PiPipeconf.ExtensionType.BMV2_JSON;
import static org.onosproject.net.pi.model.PiPipeconf.ExtensionType.P4_INFO_TEXT;

/**
 * Component that produces and registers a pipeconf when loaded.
 */
@Component(immediate = true)
public final class PipeconfFactory {

    public static final PiPipeconfId PIPECONF_ID = new PiPipeconfId("p4-tutorial-pipeconf_sgw1");
    private static final URL P4INFO_URL = PipeconfFactory.class.getResource("/mytunnel.p4info");
    private static final URL BMV2_JSON_URL = PipeconfFactory.class.getResource("/mytunnel.json");

    @Reference(cardinality = ReferenceCardinality.MANDATORY_UNARY)
    private PiPipeconfService piPipeconfService;

    @Activate
    public void activate() {
        // Registers the pipeconf at component activation.
        piPipeconfService.register(buildPipeconf());
    }

    @Deactivate
    public void deactivate() {
        piPipeconfService.remove(PIPECONF_ID);
    }

    private PiPipeconf buildPipeconf() {
        final PiPipelineModel pipelineModel;
        try {
            pipelineModel = P4InfoParser.parse(P4INFO_URL);
        } catch (P4InfoParserException e) {
            throw new IllegalStateException(e);
        }

        return DefaultPiPipeconf.builder()
                .withId(PIPECONF_ID)
                .withPipelineModel(pipelineModel)
                .addBehaviour(PiPipelineInterpreter.class, PipelineInterpreterImpl.class)
                .addBehaviour(PortStatisticsDiscovery.class, PortStatisticsDiscoveryImpl.class)
                // Since mytunnel.p4 defines only 1 table, we re-use the existing single-table pipeliner.
                .addBehaviour(Pipeliner.class, DefaultSingleTablePipeline.class)
                .addExtension(P4_INFO_TEXT, P4INFO_URL)
                .addExtension(BMV2_JSON, BMV2_JSON_URL)
                .build();
    }
}
